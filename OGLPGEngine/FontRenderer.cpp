//FontRenderer.h
#include "FontRenderer.h"

#include "Material.h"
#include "VertexDeclarations.h"
#include "Font.h"
#include "GraphicsDevice.h"

FontRenderer::FontRenderer(GameObject* owner, Material* material, Font* font, std::string text,GraphicsDevice* graphicsDevice, ComponentUpdateStep componentUpdateStep): 
	Renderer(owner, componentUpdateStep),
	_material(material), _font(font), _text(text)
{
	_vertexBuffer = std::unique_ptr<VertexBuffer>(
		new VertexBuffer(graphicsDevice, BufferType::ArrayBuffer(), BufferUsage::DynamicDraw(), sizeof(VertexPosTex),0,0));
	_vertexBuffer->AddVertexAttributeInformation(0,3,GraphicsDataType::Float(), false, sizeof(VertexPosTex), 0);
	_vertexBuffer->AddVertexAttributeInformation(1,2,GraphicsDataType::Float(), false, sizeof(VertexPosTex), sizeof(Vector3));
	_texture = std::unique_ptr<Texture2D>(new Texture2D(graphicsDevice));
}
FontRenderer::~FontRenderer()
{}

void FontRenderer::PreDraw(Camera* currentCameraComponent,GraphicsDevice* graphicsDevice)
{
	//bind the vertex buffer
	graphicsDevice->SetActiveTexture(0);
	_texture->BindTexture();

	_material->Start(graphicsDevice);
	_material->SetUniforms(graphicsDevice,currentCameraComponent);
	_vertexBuffer->BindBuffer();

	unsigned int numberOfAttributeInformations = _vertexBuffer->GetNumberOfAttributeInfos();
	for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
	{
		const VertexAttributeInformation& thisInfo = _vertexBuffer->GetVertexAttributeInformation(i);
		graphicsDevice->EnableVertexAttribute(thisInfo.GetIndex());
		graphicsDevice->SetVertexAttribute(thisInfo.GetIndex(), 
							  thisInfo.GetSize(), 
							  thisInfo.GetType(),
							  thisInfo.GetIsNormalized(), 
							  thisInfo.GetStride(), 
							  thisInfo.GetOffset());
	}
	 graphicsDevice->EnableGraphicsMode(GraphicsMode::Blend());
	 graphicsDevice->SetBlendFactor(SourceBlendFactor::SourceAlpha(), DestinationBlendFactor::OneMinusSourceAlpha());
}
void FontRenderer::Update(GameTime* gameTime, GraphicsDevice* graphicsDevice)
{
	int drawCalls = 0;
	int triangles = 0;
	_material->SetObjectUniforms(graphicsDevice, GetGameObject());

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
			ColorFormat::Red(),
			glyph->bitmap.width,
			glyph->bitmap.rows,
			0,
			ColorFormat::Red(),
			GraphicsDataType::UnsignedByte(),
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
		graphicsDevice->DrawArrays(GraphicsPrimitiveType::TriangleStrip(), 0, _vertexBuffer->GetNumberOfElements());
		drawCalls++;
		triangles += 2;
		
		x += (glyph->advance.x >> 6);
		y += (glyph->advance.y >> 6);
	}

	SetNumberOfDrawCalls(drawCalls);
	SetNumberOfTriangles(triangles);
}
void FontRenderer::PostDraw(GraphicsDevice* graphicsDevice)
{
	 graphicsDevice->DisableGraphicsMode(GraphicsMode::Blend());
	unsigned int numberOfAttributeInformations = _vertexBuffer->GetNumberOfAttributeInfos();
	for(unsigned int i = 0; i < numberOfAttributeInformations; i++)
	{
		graphicsDevice->DisableVertexAttribute(_vertexBuffer->GetVertexAttributeInformation(i).GetIndex());
	}

	_texture->UnbindTexture();
	_vertexBuffer->UnbindBuffer();
	_material->End(graphicsDevice);
}

void FontRenderer::SetText(const std::string& text)
{
	_text = text;
}
