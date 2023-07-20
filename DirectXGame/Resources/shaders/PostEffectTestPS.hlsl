#include "PostEffectTest.hlsli"
Texture2D<float4> tex0 : register(t0);
Texture2D<float4> tex1 : register(t1);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    //テクス1
    float4 colortex0 = tex0.Sample(smp, input.uv);
    //テクス2
    float4 colortex1 = tex1.Sample(smp, input.uv);
    //ブラー
    float4 blur = 0.0f;
    //テクセルサイズ
    float2 texelSize = 1.0f / float2(512, 512);

    float4 color = 1 - colortex0;


    //サンプリング範囲内のピクセルを合計
   for (int i = -1; i <= 1; ++i) 
   {
        for (int j = -1; j <= 1; ++j) 
        {
            //ピクセルの色をサンプリング
            blur += tex1.Sample(smp, input.uv + float2(texelSize.x * i, texelSize.y * j));
        }
    }

    colortex1 = blur / 8.0f;

    if (fmod(input.uv.y, 0.1f) < 0.05f) 
    {
        color = lerp(colortex0, colortex1, 0.6f);
    }

    //アルファに1を入れて出力
    return float4(color.rgb, 1);
}