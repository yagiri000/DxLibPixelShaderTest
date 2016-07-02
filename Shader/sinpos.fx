// ピクセルシェーダーの入力
struct PS_INPUT
{
	float4 DiffuseColor       : COLOR0;
	float4 SpecularColor      : COLOR1;
	float2 TextureCoord0      : TEXCOORD0;
	float2 TextureCoord1      : TEXCOORD1;
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 Output             : COLOR0;
};

// 描画するテクスチャ
sampler Texture : register(s0);

//tシフトx(外部から
float xx : register(c0);
float yy : register(c1);


PS_OUTPUT main(PS_INPUT PSInput)  //入力値
{
	PS_OUTPUT PSOutput;
	float4 TextureColor;
	float2 CalcPos;

	TextureColor = tex2D(Texture, PSInput.TextureCoord0);

	float ang = PSInput.TextureCoord0.x + (TextureColor.r + TextureColor.g + TextureColor.b)*0.1;

	CalcPos.x = cos(ang * 1000) * 0.005 + PSInput.TextureCoord0.x;
	CalcPos.y = sin(ang * 1000) * 0.005 + PSInput.TextureCoord0.y;


	TextureColor = tex2D(Texture, CalcPos);
	TextureColor.a -= 0.01;

	PSOutput.Output = TextureColor;

	return PSOutput;
}