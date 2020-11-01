// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include <cmath>

#include "tnn/layer/base_layer.h"
#include "tnn/utils/dims_vector_utils.h"

namespace TNN_NS {

DECLARE_LAYER(Expand, LAYER_EXPAND);

Status ExpandLayer::InferOutputDataType() {
    return BaseLayer::InferOutputDataType();
}

Status ExpandLayer::InferOutputShape() {
    if (input_blobs_.size() != 1) {
        return TNN_OK;
    }
    
    auto expand_param = dynamic_cast<ExpandLayerParam*>(param_);
    CHECK_PARAM_NULL(expand_param);
    Blob* input_blob = input_blobs_[0];
    Blob* output_blob = output_blobs_[0];
    auto input_dims = input_blob->GetBlobDesc().dims;
    auto shape_dims = expand_param->shape;
    auto output_dims = DimsVectorUtils::Expand(input_dims, shape_dims, nullptr);
    output_blob->GetBlobDesc().dims = output_dims;
    return TNN_OK;
}

REGISTER_LAYER(Expand, LAYER_EXPAND);

}  // namespace TNN_NS