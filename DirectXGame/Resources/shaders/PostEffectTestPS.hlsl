#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
    
    // UV指定したピクセルの色をサンプリング(UVずらし)
    //float4 texcolor = tex.Sample(smp,input.uv + float2(0.5f,0.0f));
    //アルファに1を入れて出力(UVずらし)
    //return float4(texcolor.rgb, 1);
    
    //(色反転)
    //float4 texcolor = tex.Sample(smp,input.uv);
    //RGB数値を2倍にして出力(色反転)
    //return float4(1 - texcolor.rgb,1);

    //(平均ぼかし)
    // テクスチャのサイズを指定
    int textureWidth = 512;  // テクスチャの幅
    int textureHeight = 512; // テクスチャの高さ

    // サンプリング範囲の設定
    float2 texelSize = float2(1.0 / textureWidth, 1.0 / textureHeight);

    // カーネルサイズ
    int kernelSize = 3;

    // ピクセルの初期値を設定
    float3 color = float3(0, 0, 0);

    // サンプリング範囲内のピクセルを合計
    for (int x = -kernelSize; x <= kernelSize; x++)
    {
        for (int y = -kernelSize; y <= kernelSize; y++)
        {
            float2 offset = float2(x, y) * texelSize;
            color += tex.Sample(smp, input.uv + offset).rgb;
        }
    }

    // ピクセル数で割って平均化
    color /= (kernelSize * 2 + 1) * (kernelSize * 2 + 1);

    return float4(color, 1);

}