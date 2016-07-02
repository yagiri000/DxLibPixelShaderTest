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
	
	CalcPos.x = PSInput.TextureCoord0.x;
	CalcPos.y = PSInput.TextureCoord0.y;// + 0.01;

	TextureColor = tex2D(Texture, CalcPos);

	//TextureColor.r = 1.0;
	//TextureColor.g = 1.0;
	//TextureColor.b = 1.0;

	if (TextureColor.a > 0.2){
		TextureColor.a = 0.5 + 0.5 * sin(6.28 / 0.11 * TextureColor.a);
	}else{
		TextureColor.a = 0.0;
	}

	PSOutput.Output = TextureColor;
	return PSOutput;
}