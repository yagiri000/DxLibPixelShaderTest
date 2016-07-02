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

	CalcPos.x = PSInput.TextureCoord0.x + sin(PSInput.TextureCoord0.x * 100) * 0.03;
	CalcPos.y = PSInput.TextureCoord0.y + sin(PSInput.TextureCoord0.y * 100) * 0.03;

	TextureColor = tex2D(Texture, CalcPos);
	TextureColor.a -= 0.03;
	PSOutput.Output = TextureColor;

	return PSOutput;
}