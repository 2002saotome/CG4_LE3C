#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    
    // UV指定したピクセルの色をサンプリング(UVずらし)
    float4 texcolor = tex.Sample(smp,input.uv);
    //アルファに1を入れて出力(UVずらし)
    return float4(texcolor.rgb, 1);
    
   
}