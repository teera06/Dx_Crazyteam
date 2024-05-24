#include "ContentShaderBase.hlsli"

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};


ImageVSOutPut FadeInOut_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    Out.POSITION = _Input.POSITION;
    Out.TEXCOORD = _Input.TEXCOORD/* * 0.5f*/;
    return Out;
}

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

TextureSet(Image, 0)


ImagePSOutPut FadeInOut_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    Out.COLOR.rgba = Image.Sample(Image_Sampler, _Input.TEXCOORD.xy);


    Out.COLOR.rgb -= Image.Sample(Image_Sampler, _Input.TEXCOORD.xy) * AccTime * 0.5f;
    if (Out.COLOR.r < float(0.f) || Out.COLOR.g < float(0.f) || Out.COLOR.b < float(0.f))
    {
         Out.COLOR.rgba = float4(0.f, 0.f, 0.f, 1.f);
    }
    
    
    
     return Out;
}
