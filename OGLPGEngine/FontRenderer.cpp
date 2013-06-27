//FontRenderer.h
#include "FontRenderer.h"

#include "Material.h"
#include "VertexDeclarations.h"
#include "Font.h"

FontRenderer::FontRenderer(GameObject* owner, Material* material, Font* font, std::string text, ComponentUpdateStep componentUpdateStep): 
	Renderer(owner, componentUpdateStep),
	_material(material), _font(font), _text(text)
{
	_vertexBuffer = std::unique_ptr<VertexBuffer>(
		new VertexBuffer(BufferType::ArrayBuffer(), BufferUsage::DynamicDraw(), sizeof(VertexPosTex),0,0));
	_vertexBuffer->AddVertexAttributeInformation(0,3,GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), 0);
	_vertexBuffer->AddVertexAttributeInformation(1,2,GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), sizeof(Vector3));
	_texture = std::unique_ptr<Texture2D>(new Texture2D());
}
FontRenderer::~FontRenderer()
{}

void FontRenderer::PreDraw(Camera* currentCameraComponent)
{
	//bind the vertex buffer
	glActiveTexture( GL_TEXTURE0 );
	_texture->BindTexture();

	_material->Start();
	_material->SetUniforms(currentCameraComponent);
	_vertexBuffer->BindBuffer();

	unsigned int numberOfAttributeInformations = _vertexBuffer->GetNumberOfAttributeInfos();
	for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
	{
		const VertexAttributeInformation& thisInfo = _vertexBuffer->GetVertexAttributeInformation(i);
		glEnableVertexAttribArray(thisInfo.GetIndex());
		glVertexAttribPointer(thisInfo.GetIndex(), 
							  thisInfo.GetSize(), 
							  thisInfo.GetType(),
							  thisInfo.GetIsNormalized(), 
							  thisInfo.GetStride(), 
							  thisInfo.GetOffset());
	}
	 glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void FontRenderer::Update(GameTime* gameTime)
{
	int drawCalls = 0;
	int triangles = 0;
	_material->SetObjectUniforms(GetGameObject());

	//int glerror = glGetError();
	float x = 0;
	float y = 0;
	const char* p;
	for(p = _text.c_str(); *p; p++)
	{
		if(!_font->LoadCharacter(*p))
		{
			continue;
		}

		FT_GlyphSlot glyph = _font->GetFace()->glyph;
		//glerror = glGetError();
		_texture->SetTextureData(
			0,
			GL_RED,
			glyph->bitmap.width,
			glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			glyph->bitmap.buffer);
		//glerror = glGetError();
		float x2 = x + glyph->bitmap_left;
		float y2 = -y - glyph->bitmap_top;
		float w = (float)glyph->bitmap.width;
		float h = (float)glyph->bitmap.rows;

		VertexPosTex vertexData[4] = 
		{
			VertexPosTex(Vector3(x2,		y2, 0),		Vector2(0,0)),
			VertexPosTex(Vector3(x2,	y2 + h, 0),		Vector2(0,1)),
			VertexPosTex(Vector3(x2 + w,		y2, 0),	Vector2(1,0)),
			VertexPosTex(Vector3(x2 + w,	y2 + h, 0),	Vector2(1,1)),
		};
		_vertexBuffer->SetBufferData(4, vertexData);
		glDrawArrays(GL_TRIANGLE_STRIP,0, _vertexBuffer->GetNumberOfElements());
		drawCalls++;
		triangles += 2;
		
		x += (glyph->advance.x >> 6);
		y += (glyph->advance.y >> 6);
	}

	SetNumberOfDrawCalls(drawCalls);
	SetNumberOfTriangles(triangles);
}
void FontRenderer::PostDraw()
{
	glDisable(GL_BLEND);
	unsigned int numberOfAttributeInformations = _vertexBuffer->GetNumberOfAttributeInfos();
	for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
	{
			glDisableVertexAttribArray(_vertexBuffer->GetVertexAttributeInformation(i).GetIndex());
	}

	_texture->UnbindTexture();
	_vertexBuffer->UnbindBuffer();
	_material->End();
}

void FontRenderer::SetText(std::string text)
{
	_text = text;
}
