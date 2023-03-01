//
// Created by TCY on 2023/3/1.
//

#ifndef CS_ASSIGNMENTS_WINDOWSTYLE_H
#define CS_ASSIGNMENTS_WINDOWSTYLE_H

// enum to store the style of the window
enum Style {
    Sizable = 0b11111011,  // 11111_11
    Dialog = 0b01000010,  // 01000_10
    Single = 0b11111010,  // 11111_10
    None = 0b00000000,  // 00000_0-
    Tool = 0b00001000,  // 00001_0-
    SizableTool = 0b00001011  // 00001_11
};

// structure to store the status of each element
union Status{
    struct Binary_Status{
        // Board
        bool Resizer : 1;
        bool Edge : 1;
        bool : 1;
        // Title Bar
        bool Close : 1;
        bool Minimize : 1;
        bool Maximize : 1;
        bool Caption : 1;
        bool Icon : 1;
    } Bi_Status;
    unsigned char Char_Status;
    // construct Status using unsigned char (also change the struct)
    Status(unsigned char style = None) {
        Char_Status = style;
    }
};

class WindowStyle {
private:
    Status CurrentStatus;
public:
    WindowStyle(unsigned char style = None) : CurrentStatus(style) {}

    bool IsIconShown() const {
        return CurrentStatus.Bi_Status.Icon;
    }

    bool IsCaptionShown() const {
        return CurrentStatus.Bi_Status.Caption;
    }

    bool IsMaximizeShown() const {
        return CurrentStatus.Bi_Status.Maximize;
    }

    bool IsMinimizeShown() const {
        return CurrentStatus.Bi_Status.Minimize;
    }

    bool IsCloseShown() const {
        return CurrentStatus.Bi_Status.Close;
    }

    bool IsTitleBarShown() const {
        return CurrentStatus.Bi_Status.Icon ||
        CurrentStatus.Bi_Status.Caption ||
        CurrentStatus.Bi_Status.Maximize ||
        CurrentStatus.Bi_Status.Minimize ||
        CurrentStatus.Bi_Status.Close;
    }

    bool IsEdgeShown() const {
        return CurrentStatus.Bi_Status.Edge;
    }

    bool IsResizerShown() const {
        return CurrentStatus.Bi_Status.Resizer && CurrentStatus.Bi_Status.Edge;
    }

    bool IsBoardShown() const {
        return CurrentStatus.Bi_Status.Edge;
    }

    Status& GetStatus() {
        return CurrentStatus;
    }
};

#endif //CS_ASSIGNMENTS_WINDOWSTYLE_H
