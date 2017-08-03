#ifndef _WING_ENGINE_CONSTANT_H_
#define _WING_ENGINE_CONSTANT_H_

#define INVALID_LOCALTION -1
#define INVALID_PROGRAM -1
#define INVALID_TEXTURE -1
#define INVALID_BUFFERS 0

#define MAX_LIGHT 5

enum PluginType
{
	PluginTypeNull,
	PluginTypeRenderer,
};

//resource type
enum ResourceType
{
	ResourceTypeNull,
	ResourceTypeConfig,
	ResourceTypeImage,
	ResourceTypeMesh,
	ResourceTypeMax,
};

//render type
enum RenderType
{
	RenderTypeNULL,
	RenderTypeGeometry,
	RenderTypeMesh,
};


//data element type
enum DataElementType
{
	DataElementUByte,
	DataElementByte,
	DataElementUShort,
	DataElementShort,
	DataElementUInt,
	DataElementInt,
	DataElementULong,
	DataElementLong,
	DataElementReal,
};

enum DataElementName
{
	DataElementIndice,
	DataElementPosition,
	DataElementNormal,
	DataElementTexture,
	DataElementColor,
};

enum ColorFormat
{
	ColorFormatRGBA8,
	ColorFormatRGB,
	ColorFormatRGBA,
	ColorFormatDepth,
};

enum LightType
{
	LightTypeNull,
	LightTypePoint,
	LightTypeDirection,
};

enum TextureType
{
	TextureTypeNull,
	TextureTypeRGB,
	TextureTypeRGBA,
	TextureTypeDepth,
};

enum TextureFormat
{
	TextureFormatAlpha,
	TextureFormatDepth,
	TextureFormatLumince,
	TextureFormatLuminceAlpha,	//灰度值+透明度
	TextureFormatIntensity,		//亮度
	TextureFormatRGB,
	TextureFormatRGBA,
};

enum AttachmentPoint
{
	AttachmentPointColor0,
	AttachmentPointColor1,
	AttachmentPointColor2,
	AttachmentPointColor3,
	AttachmentPointColor4,
	AttachmentPointColor5,
	AttachmentPointDepth,
	AttachmentPointStencil,
};



#endif