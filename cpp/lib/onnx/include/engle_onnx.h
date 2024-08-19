#pragma once

#include <iostream>
#include "onnxruntime_cxx_api.h"
#include "onnxruntime_c_api.h"
#include "ort_genai.h"
#include "ort_genai_c.h"

/**
 * A Singleton pattern to store instance of Onnxruntime
 */
class EngleOnnx
{

public:
    static bool init(const std::string &modelPath);
    static EngleOnnx& getInstance(const std::string & modelPath = "");
    const std::string infer(const std::string &userInput);
    
    EngleOnnx (EngleOnnx &) = delete;
    EngleOnnx & operator=(const EngleOnnx &) = delete;

private:    
    
    static void privateInit(const std::string &modelPath);
    EngleOnnx (const std::string & directory);

    std::unique_ptr<OgaModel> session;
    std::unique_ptr<OgaTokenizer> tokenizer;
    std::string modelPath;

    // the reference to the singleton instance
    static EngleOnnx * instance;
};
