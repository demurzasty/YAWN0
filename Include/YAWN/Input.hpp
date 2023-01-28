#pragma once 

#include "Vector2.hpp"

namespace YAWN {
	enum class KeyCode {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,

        Apostrophe,
        Minus,
        Escape,
        LeftControl,
        LeftShift,
        LeftAlt,
        LeftSystem,
        RightControl,
        RightShift,
        RightAlt,
        RightSystem,
        Menu,
        LeftBracket,
        RightBracket,
        Semicolon,
        Comma,
        Period,
        Quote,
        Slash,
        Backslash,
        Tilde,
        Equal,
        Hyphen,
        Space,
        Enter,
        Backspace,
        Tab,
        PageUp,
        PageDown,
        End,
        Home,
        Insert,
        Del,
        Add,
        Subtract,
        Multiply,
        Divide,
        Left,
        Right,
        Up,
        Down,

        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,

        Numpad0,
        Numpad1,
        Numpad2,
        Numpad3,
        Numpad4,
        Numpad5,
        Numpad6,
        Numpad7,
        Numpad8,
        Numpad9,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,

        Pause
	};

	enum class MouseButton {
        Left,
        Right,
        Middle
	};

    enum class InputEventType {
        Key,
        MouseMove,
        MouseButton
    };

    class InputEventKey {
    public:
        KeyCode Key;
    };

    class InputEventMouseMove {
    public:
        Vector2 Position;
    };

    class InputEventMouseButton {
    public:
        Vector2 Position;
        MouseButton Button;
        bool Pressed;
    };

    class InputEvent {
    public:
        InputEventType Type;
        union {
            InputEventKey Key;
            InputEventMouseMove MouseMove;
            InputEventMouseButton MouseButton;
        };
    };
}
