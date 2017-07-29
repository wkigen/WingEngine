#ifndef _WING_ENGINE_CONSTANT_H_
#define _WING_ENGINE_CONSTANT_H_

#define INVALID_LOCALTION -1
#define INVALID_PROGRAM -1
#define INVALID_TEXTURE -1
#define INVALID_BUFFERS 0


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
	ColorFormatRGB,
	ColorFormatRGBA,
};


enum  PluginType
{
	PluginTypeNull,
	PluginTypeRenderer,
};

#endif