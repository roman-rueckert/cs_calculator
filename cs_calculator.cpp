#include <QtCore>
#include <QtGui>

class Calculator : public QWidget
{

private:
    QLineEdit *display;
    QGridLayout *layout;
    QList<QPushButton*> buttons;
    double number_1 = 0, number_2 = 0, result = 0;
    char operation = '\0';
    QString lastInput;

    const QStringList buttons_vals = {"7", "8", "9", "+",
                                      "4", "5", "6", "-",
                                      "1", "2", "3", "*",
                                      ".", "0", "=", "/"
                                     };

    void performCalculation();
    void buttonClicked();
    void clearDisplay();

public:
    Calculator();
};

Calculator::Calculator()
{
    // Init UI
    display = new QLineEdit("0");
    layout = new QGridLayout(this);
    layout->addWidget(display, 0, 0, 1, 4);

    for (int i = 0; i < buttons_vals.length(); i++) {
        QPushButton *button = new QPushButton(buttons_vals[i], this);
        buttons.append(button);
        layout->addWidget(button, (i)/4 + 1, (i)%4);
        connect(button, &QPushButton::clicked, this, &Calculator::buttonClicked);
    }

    QPushButton *clear = new QPushButton("C", this);
    layout->addWidget(clear, 5, 3);
    connect(clear, &QPushButton::clicked, this, &Calculator::clearDisplay);

    setMinimumSize(300, 400);
    setWindowTitle("Calculator v 0.1");

    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(40);
}

void Calculator::buttonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonText = button->text();
    if (buttons_vals.contains(buttonText)) {
        std::string str = buttonText.toStdString();
        switch (str[0]) {
        case '+':
            number_1 = display->text().toDouble();
            operation = '+';
            display->clear();
            break;
        case '-':
            number_1 = display->text().toDouble();
            operation = '-';
            display->clear();
            break;
        case '*':
            number_1 = display->text().toDouble();
            operation = '*';
            display->clear();
            break;
        case '/':
            number_1 = display->text().toDouble();
            operation = '/';
            display->clear();
            break;
        case '=':
            performCalculation();
            break;
        case '.':
            if (!display->text().contains(".")) {
                display->insert(".");
            }
            break;
        default:
            if (display->text() == "0") {
                display->clear();
            }
            lastInput = buttonText;
            display->setText(display->text() + lastInput);
            break;
        }
    }
}

void Calculator::performCalculation() {
    number_2 = display->text().toDouble();

    // Cannot divide by zero
    if (number_2 == 0 && operation == '/') {
        display->setText("ERROR: Cannot divide by zero");
        return;
    }

    switch (operation) {
    case '+':
        result = number_1 + number_2;
        break;
    case '-':
        result = number_1 - number_2;
        break;
    case '*':
        result = number_1 * number_2;
        break;
    case '/':
        result = number_1 / number_2;
        break;
    default:
        display->setText("Invalid Operation");
        return;
    }
    display->setText(QString::number(result));
}

void Calculator::clearDisplay()
{
    display->clear();
    display->setText("0");
    number_1 = 0.0;
    number_2 = 0.0;
    result = 0.0;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Calculator *window = new Calculator();
    window->show();
    int retVal = app.exec();

    delete window;
    return retVal;
}