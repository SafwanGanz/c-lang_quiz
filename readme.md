# 🎯 Modern Quiz Application

A sleek, interactive command-line quiz application written in C that features a modern UI design and cross-platform compatibility.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)

## ✨ Features

- 🎨 Modern console-based UI with borders and colors
- 📊 Real-time progress tracking with visual progress bar
- ✅ Immediate feedback on answers
- 📱 Cross-platform compatibility (Windows, macOS, Linux)
- 🎯 Performance scoring with personalized feedback
- 🔄 Easy question customization

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Basic terminal/command prompt knowledge

### Installation

1. Clone the repository
```bash
git clone https://github.com/yourusername/modern-quiz-app.git
cd modern-quiz-app
```

2. Compile the application
```bash
gcc quiz.c -o quiz
```

3. Run the quiz
```bash
./quiz  # On Unix-like systems
quiz.exe  # On Windows
```

## 🎮 Usage

1. Launch the application
2. Press Enter to start the quiz
3. For each question:
   - Read the question carefully
   - Choose your answer (A/B/C/D)
   - Get immediate feedback
   - Press Enter to continue
4. View your final score and performance assessment

## 🛠️ Customization

### Adding New Questions

Edit the `questions` array in `quiz.c`:

```c
Question questions[] = {
    {
        "Your question here?",
        {"Option A", "Option B", "Option C", "Option D"},
        correct_answer_index  // 0 for A, 1 for B, 2 for C, 3 for D
    },
    // Add more questions...
};
```

### Color Scheme

Modify the `setConsoleColor()` function calls with different color codes:
- 2: Green
- 3: Cyan
- 6: Yellow
- 7: White
- 10: Bright Green
- 11: Bright Cyan
- 12: Bright Red
- 14: Bright Yellow

## 🎨 UI Elements

The application features several UI components:
- Bordered question boxes
- Centered text alignment
- Dynamic progress bar
- Color-coded feedback
- Clean, consistent spacing

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by modern CLI applications
- Built with cross-platform compatibility in mind
- Designed for educational purposes

## 📞 Contact

Your Name - [@yourusername](https://twitter.com/yourusername)

Project Link: [https://github.com/yourusername/modern-quiz-app](https://github.com/yourusername/modern-quiz-app)
