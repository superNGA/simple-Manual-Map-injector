//=========================================================================
//                      CONSOLE SYSTEM V2
//=========================================================================
// by      : INSANE
// created : 07/03/2025
// 
// purpose : easier and better console output / printing.
//-------------------------------------------------------------------------

#pragma once

#define ENABLE_CONSOLE 1 // set to 0 to disable console

//======================= COLOR MACROS =======================
// text colors
enum consTextClr_t
{
    FG_INVALID = -1,
    FG_BLACK = 30,
    FG_RED = 31,
    FG_GREEN = 32,
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_MAGENTA = 35,
    FG_CYAN = 36,
    FG_WHITE = 37
};

//Background color
enum consBgClr_t
{
    BG_BLACK = 40,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_YELLOW = 43,
    BG_BLUE = 44,
    BG_MAGENTA = 45,
    BG_CYAN = 46,
    BG_WHITE = 47
};

//Text format
enum consTextFormat_t
{
    NORMAL = 0,
    BOLD = 1,
    UNDERLINE = 4,
};

//======================= FN MACROS =======================
#if ENABLE_CONSOLE == 1

#define CONS_INITIALIZE(introClr)   cons.inititalize(introClr)
#define CONS_INITIALIZE()   cons.inititalize()
#define CONS_UNINITIALIZE() cons.uninitialize()
#define DRAW_DEVIDER()      cons.drawDevider()

// error & sucess logs
#define CONS_LOG_ERROR(errorMessage) cons.Log(consTextClr_t::FG_RED, consBgClr_t::BG_BLACK, consTextFormat_t::BOLD, __FUNCTION__, false, errorMessage)
#define CONS_LOG_SUCCESS(Message) cons.Log(consTextClr_t::FG_GREEN, consBgClr_t::BG_BLACK, consTextFormat_t::BOLD, __FUNCTION__, false, Message)

// text logs
#define CONS_FASTLOG(textColor, logMessage, ...) cons.Log(textColor, consBgClr_t::BG_BLACK, consTextFormat_t::BOLD, __FUNCTION__, false, logMessage, ##__VA_ARGS__)
#define CONS_FASTLOGWT(textColor, logMessage, ...) cons.Log(textColor, consBgClr_t::BG_BLACK, consTextFormat_t::BOLD, __FUNCTION__, true, logMessage, ##__VA_ARGS__)
#define CONS_LOG(textColor, BGColor, textFormat, logmessage, ...) cons.Log(textColor, BGColor, textFormat, __FUNCTION__, false, logmessage, ##__VA_ARGS__)
#define CONS_LOGWT(textColor, BGColor, textFormat, logmessage, ...) cons.Log(textColor, BGColor, textFormat, __FUNCTION__, true, logmessage, ##__VA_ARGS__)

// float arrays / struct logs
#define CONS_FASTLOG_FLOAT_ARR(pFloatArr) cons.LogFloatArr(consTextClr_t::FG_CYAN, consBgClr_t::BG_BLACK, consTextFormat_t::BOLD, __FUNCTION__, false, #pFloatArr, (void*)&pFloatArr, sizeof(pFloatArr))
#define CONS_FASTLOG_FLOAT_ARRWT(pFloatArr) cons.LogFloatArr(consTextClr_t::FG_CYAN, consBgClr_t::BG_BLACK, consTextFormat_t::BOLD, __FUNCTION__, true, #pFloatArr, (void*)&pFloatArr, sizeof(pFloatArr))
#define CONS_LOG_FLOAT_ARR(textColor, BGColor, textFormat, pFloatArr) cons.LogFloatArr(textColor, BGColor, textFormat, __FUNCTION__, false, #pFloatArr, (void*)&pFloatArr, sizeof(pFloatArr))
#define CONS_LOG_FLOAT_ARRWT(textColor, BGColor, textFormat, pFloatArr) cons.LogFloatArr(textColor, BGColor, textFormat, __FUNCTION__, true, #pFloatArr, (void*)&pFloatArr, sizeof(pFloatArr))

#else

#define CONS_INITIALIZE(introClr)                                       void(0)
#define CONS_INITIALIZE()                                               void(0)
#define CONS_UNINITIALIZE()                                             void(0)
#define DRAW_DEVIDER()                                                  void(0)
#define CONS_LOG_ERROR(errorMessage)                                    void(0)
#define CONS_LOG_SUCCESS(Message)                                       void(0)
#define CONS_FASTLOG(textColor, logMessage, ...)                        void(0)
#define CONS_FASTLOGWT(textColor, logMessage, ...)                      void(0)
#define CONS_LOG(textColor, BGColor, textFormat, logmessage, ...)       void(0)
#define CONS_LOGWT(textColor, BGColor, textFormat, logmessage, ...)     void(0)
#define CONS_FASTLOG_FLOAT_ARR(pFloatArr)                               void(0)
#define CONS_FASTLOG_FLOAT_ARRWT(pFloatArr)                             void(0)
#define CONS_LOG_FLOAT_ARR(textColor, BGColor, textFormat, pFloatArr)   void(0)
#define CONS_LOG_FLOAT_ARRWT(textColor, BGColor, textFormat, pFloatArr) void(0)

#endif // ENABLE_CONSOLE


#include <iostream>
#include <string>
#include <vector>

class ConsoleSystem_t
{
public:
    ConsoleSystem_t();
    bool inititalize(consTextClr_t introClr = FG_INVALID);
    void uninitialize();

    void drawDevider();
    void Log(consTextClr_t textColor, consBgClr_t BGColor, consTextFormat_t format, const char* tag, bool showTimeInstead, const char* logMessage...);
    void LogFloatArr(consTextClr_t textColor, consBgClr_t BGColor, consTextFormat_t format, const char* tag, bool showTimeInstead, const char* varName, void* pFloatArr, uint32_t size);

    // character used for printing devider
    const char* deviderCharacter = "=";
    
private:
    bool _isConsoleAllocated();
    bool _allocateConsole();
    void _printIntro(consTextClr_t introClr);
    int _getConsoleWidth();
    bool _isPrinting = false;
    bool _isInitialized = false;

    std::vector<std::string> _intro;
};
extern ConsoleSystem_t cons;