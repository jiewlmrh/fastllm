//
// Created by huangyuyang on 6/1/23.
//

#ifndef FASTLLM_MINICPM_H
#define FASTLLM_MINICPM_H

#include "basellm.h"
#include "llama.h"
#include "cmath"

#include <iostream>

namespace fastllm {
    class MiniCpmModel: public LlamaModel {
    public:
        MiniCpmModel(); // 构造函数

        virtual void InitParams(); // 初始化参数信息

        // 推理
        virtual int Forward(
                const Data &inputIds,
                const Data &attentionMask,
                const Data &positionIds,
                std::vector <std::pair <Data, Data> > &pastKeyValues,
                const GenerationConfig &generationConfig = GenerationConfig(),
                const LastTokensManager &lastTokens = LastTokensManager(),
                std::vector <float> *logits = nullptr);

        std::vector <int> ForwardBatch(
                int batch,
                const Data &inputIds,
                const Data &attentionMask,
                const Data &positionIds,
                std::vector <std::pair <Data, Data> > &pastKeyValues,
                const GenerationConfig &generationConfig = GenerationConfig(),
                const LastTokensManager &lastTokens = LastTokensManager(),
                std::vector <std::vector <float>*> *logits = nullptr);

        std::vector <int> ForwardBatch(
                int batch,
                const Data &inputIds,
                const std::vector <Data*> &attentionMask,
                const std::vector <Data*> &positionIds,
                const std::vector <int> &seqLens,
                std::vector <std::pair <Data*, Data*> > &pastKeyValues,
                const std::vector <GenerationConfig> &generationConfigs,
                const LastTokensManager &lastTokens = LastTokensManager(),
                std::vector <std::vector <float>*> *logits = nullptr);

    private:
        float embed_scale = 1.f;

        float attention_scale = 1.f / std::sqrt(block_cnt);

        float rms_scale = 1.f / 4096.f;
    };
}

#endif //FASTLLM_MINICPM_H
