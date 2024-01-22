// Copyright (C) 2018-2023 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "shared_test_classes/single_layer/cum_sum.hpp"

namespace LayerTestsDefinitions {

std::string CumSumLayerTest::getTestCaseName(const testing::TestParamInfo<cumSumParams>& obj) {
    InferenceEngine::SizeVector inputShapes;
    InferenceEngine::Precision inputPrecision;
    int64_t axis;
    bool exclusive, reverse;
    std::string targetDevice;
    std::tie(inputShapes, inputPrecision, axis, exclusive, reverse, targetDevice) = obj.param;

    std::ostringstream result;
    result << "IS=" << ov::test::utils::vec2str(inputShapes) << "_";
    result << "Precision=" << inputPrecision.name() << "_";
    result << "Axis=" << axis << "_";
    result << "Exclusive=" << (exclusive ? "TRUE" : "FALSE") << "_";
    result << "Reverse=" << (reverse ? "TRUE" : "FALSE") << "_";
    result << "TargetDevice=" << targetDevice;
    return result.str();
}

void CumSumLayerTest::SetUp() {
    InferenceEngine::SizeVector inputShapes;
    InferenceEngine::Precision inputPrecision;
    bool exclusive, reverse;
    int64_t axis;
    std::tie(inputShapes, inputPrecision, axis, exclusive, reverse, targetDevice) = this->GetParam();
    const auto inType = FuncTestUtils::PrecisionUtils::convertIE2nGraphPrc(inputPrecision);
    const auto paramData = std::make_shared<ov::op::v0::Parameter>(inType, ov::Shape(inputShapes));
    const auto axisNode = std::make_shared<ov::op::v0::Constant>(ov::element::Type_t::i64, ov::Shape{}, std::vector<int64_t>{axis})->output(0);
    const auto cumSum = std::make_shared<ov::op::v0::CumSum>(paramData, axisNode, exclusive, reverse);

    ov::ResultVector results{std::make_shared<ov::op::v0::Result>(cumSum)};
    function = std::make_shared<ov::Model>(results, ov::ParameterVector{paramData}, "cumsum");
}
}  // namespace LayerTestsDefinitions
