#pragma once

/////////////////////////////////////////////////////////////////////////////
// CErrorLogger

/// <summary>
/// Клас за записване на грешки
/// </summary>
class CErrorLogger
{
    // Constants
    // ----------------
private:
    /// <summary> Пътят към файла за грешки </summary>
    static const char* _szFilepath;

    // Constructor / Destructor
    // ----------------
public:

    // Methods
    // ----------------
private:
    /// <summary> Записва на грешка във файл </summary>
    static void LogErrorToFile(const CString& strError);

    /// <summary> Показва на грешка като съобщение </summary>
    static void LogErrorAsMessage(const CString& strError);

public:
    /// <summary> Запазва/показва съобщение </summary>
    static void LogMessage(const CString& strError, const BOOL bToFile, const BOOL bAsMessage);

    // Overrides
    // ----------------

    // Members
    // ----------------
};

