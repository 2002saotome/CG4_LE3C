#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
public:
    ///<summary>
    ///コンストラクタ
    ///</summary>
    PostEffect();

    ///<summary>
    ///描画コマンドの発行
    ///</summary>
    /// <param name="cmdList">コマンドリスト</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);
};

