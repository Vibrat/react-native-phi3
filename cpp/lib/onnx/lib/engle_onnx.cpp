#include <iostream>
#include <sstream>
#include "engle_onnx.h"
#include "engle_utils.h"

// static place to store the instance
EngleOnnx *EngleOnnx::instance = nullptr;

EngleOnnx::EngleOnnx(const std::string &directory)
{
    std::cout << "create instance of EngleOnnx " << directory << std::endl;
    if (!EngleUtils::isDirectory(directory))
    {
        std::stringstream errMsg;
        errMsg << "Model path does not exist for " << directory;
        throw std::logic_error(errMsg.str());
    }
    session = OgaModel::Create(directory.c_str());
    tokenizer = OgaTokenizer::Create(*session);
    modelPath = std::move(directory);
}

/**
 * Return yes/ no if the module is initialized correctly.
 */
bool EngleOnnx::init(const std::string &directory)
{
    if (instance == nullptr)
    {
        try
        {
            instance = new EngleOnnx(directory);
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error while intialize model \n"
                      << e.what() << std::endl;
        }
    }
    else
    {
        std::cerr << "Instance of Phi3 model already exist" << std::endl;
        return true;
    }
    return false;
}

void EngleOnnx::privateInit(const std::string &directory)
{
    // creating an instance for the first time
    if (instance == nullptr)
    {
        instance = new EngleOnnx(directory);
    }
}

EngleOnnx &EngleOnnx::getInstance(const std::string &directory)
{
    privateInit(directory);
    return *instance;
}

const std::string EngleOnnx::infer(const std::string &userText)
{   
    // throw error for user's to know about the malform
    if (instance == nullptr) {
        throw std::runtime_error("model has not been initialized");    
        return nullptr;
    }

    // if tokenizer is null we also not doing anything here
    if (!tokenizer)
    {
        throw std::runtime_error("Tokenizer is not initialized.");
    }

    std::string prompt = "<|user|>\n" + userText + "<|end|>\n<|assistant|>";
    auto sequences = OgaSequences::Create();
    const char *promptCString = prompt.c_str();
    tokenizer->Encode(promptCString, *sequences);

    auto params = OgaGeneratorParams::Create(*session);
    params->SetSearchOption("max_length", 200);
    params->SetInputSequences(*sequences);

    auto tokenizer_stream = OgaTokenizerStream::Create(*tokenizer);
    auto generator = OgaGenerator::Create(*session, *params);

    std::string response = "";

    while (!generator->IsDone())
    {

        std::cout << "Computing Logits" << std::endl;
        generator->ComputeLogits();
        generator->GenerateNextToken();

        const int32_t *seq = generator->GetSequenceData(0);
        size_t seq_len = generator->GetSequenceCount(0);
        const char *decode_tokens = tokenizer_stream->Decode(seq[seq_len - 1]);

        response += decode_tokens;
    }

    return response;
}
