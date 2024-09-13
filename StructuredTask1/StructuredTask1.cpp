#include <iostream>
#include <algorithm>
#include <sstream>
#include <memory>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
    virtual ~Text() = default; // Добавляем виртуальный деструктор
};

class DecoratedText : public Text {
public:
    std::shared_ptr<Text> text_; // Используем shared_ptr вместо сырых указателей
    explicit DecoratedText(std::shared_ptr<Text> text) : text_(text) {}
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::string text2 = data;
        std::reverse(text2.begin(), text2.end());
        text_->render(text2);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data, const std::string& data2) const {
        std::stringstream strm;
        strm << "<a href=\"" << data << "\">" << data2 << "</a>";
        std::string text2 = strm.str();
        text_->render(text2);
    }
};

int main()
{
    auto text_block = std::make_shared<Paragraph>(std::make_shared<Text>());
    text_block->render("Hello world");

    std::cout << "\n" << std::endl;

    auto text_block2 = std::make_shared<Reversed>(std::make_shared<Text>());
    text_block2->render("Hello world");

    std::cout << "\n" << std::endl;

    auto text_block3 = std::make_shared<Link>(std::make_shared<Text>());
    text_block3->render("netology.ru", "Hello world");
}
