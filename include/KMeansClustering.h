/*************************
 * @file KMeansClustering.h
 * @author Zhile Zhu (zhuzhile08@gmail.com)
 * 
 * @brief Main KMeansClustering assignment
 * 
 * @date 2024-05-15
 * @copyright Copyright (c) 2024
 *************************/

#pragma once

#include <Common/FileSystem.h>
#include <Common/Logger.h>
#include <Common/JSON.h>
#include <Common/Vector.h>
#include <Common/UnorderedSparseMap.h>

class KMeansClustering {
public:
    KMeansClustering() : m_data(lstd::Json::parse(lstd::StringStream("data/data.json").data())) { }

    void visualizeData();

private:
    lstd::Json m_data;
};
