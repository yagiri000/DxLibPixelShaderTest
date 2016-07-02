// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float4 DiffuseColor       : COLOR0;
	float4 SpecularColor      : COLOR1;
	float2 TextureCoord0      : TEXCOORD0;
	float2 TextureCoord1      : TEXCOORD1;
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
	float4 Output             : COLOR0;
};

// �`�悷��e�N�X�`��
sampler Texture : register(s0);

//t�V�t�gx(�O������
float xx : register(c0);
float yy : register(c1);


PS_OUTPUT main(PS_INPUT PSInput)  //���͒l
{
	PS_OUTPUT PSOutput;
	float4 TextureColor;
	float2 CalcPos;


	TextureColor = tex2D(Texture, PSInput.TextureCoord0);

	float tx = PSInput.TextureCoord0.x;
	float ty = PSInput.TextureCoord0.y;
	float dx = PSInput.TextureCoord0.x - xx;
	float dy = PSInput.TextureCoord0.y - yy;
	float dist = dx * dx + dy * dy;

	CalcPos.x = tx + 0.003 * cos(fmod(dy * dy, 0.01) * 1000 + tx);
	CalcPos.y = ty + 0.003 * sin(fmod(dx * dx, 0.01) * 1000 + tx);

	TextureColor = tex2D(Texture, CalcPos);
	TextureColor.a -= 0.01;

	PSOutput.Output = TextureColor;

	return PSOutput;
}