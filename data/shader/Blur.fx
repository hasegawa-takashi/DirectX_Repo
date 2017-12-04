// モーションブラー
string XFile = "misc/nanase_pose.x";
int BCLR = 0x000000ff;

//変換マトリックス
float4x4 matWVP : WORLDVIEWPROJECTION;
float4x4 matWV  ; WORLDVIEW;
float4x4 matW   : WORLD;
float4x4 matP   : PROJECTION;

float4x4 matWVold;

float3 camera : CAMERAPOSITION;

float3 light <string UIDirectional = "Light Direction";> = {-0.35f,-0.25f,0.9f};

float4 I_d = {1.0f,1.0f,1.0f,1.0f};
float4 I_a = {0.2f,0.2f,0.2f,1.0f};
float4 I_s = {1.0f,1.0f,1.0f,1.0f};

float4 k_d : MATERIALDIFFUSE;
float4 k_s : MATERIALSPECULAR;
float  k_p : MATERIALPOWER;
float4 k_a : MATERIALAMBIENT;
texture tex : MATERIALTEXTURE;
bool tex_enable : MATERIALTEXTUREVALID;

texture g_texture;
texture VelocityMap;

sampler Sampler = sampler_state
{
	Texture = (tex);
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

sampler CopySampler = sampler_state
{
	Texture = <g_texture>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

sampler VelocitySampler = sampler_state
{
	Texture = <VelocityMap>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

void PhongVS(float4 InPos : POSITION,
	float3 InNor : NORMAL,
	float2 InTex : TexCOORD0, 
	out float4 OutPos : POSITION,
	out float2 OutTex : TEXCOORD0,
	out float3 OutWPos : TEXCOORD1,
	out float3 OutWNor : TEXCOORD2,
	)
{

	OutPos = mul(InPos,matWVP);
	OutTex = InTex;
	OutWPos = mul(InPos,matW).xyz;
	OutWNor = mul(InNor,(float3x3)matW);
}