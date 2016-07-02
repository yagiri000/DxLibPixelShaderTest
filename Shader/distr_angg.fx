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

PS_OUTPUT main(PS_INPUT PSInput)  //入力値
{
	PS_OUTPUT PSOutput;
	float4 TextureColor;
	float2 CalcPos;
	float hoge;
	TextureColor = tex2D(Texture, PSInput.TextureCoord0);
	hoge = TextureColor.r + TextureColor.g + TextureColor.b;

	CalcPos.x = PSInput.TextureCoord0.x + 0.02 * TextureColor.a * cos(TextureColor.b * 6.28 * 5 + 1.57);
	CalcPos.y = PSInput.TextureCoord0.y + 0.02 * TextureColor.a * sin(TextureColor.b * 6.28 * 5 + 1.57);

	TextureColor = tex2D(Texture, CalcPos);
	TextureColor.a -= 0.00;
	TextureColor.rgb -= 0.03;
	PSOutput.Output = TextureColor;

	return PSOutput;
}