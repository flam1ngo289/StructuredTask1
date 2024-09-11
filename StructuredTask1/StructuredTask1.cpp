#include <iostream>
#include <algorithm>
#include <sstream>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
public:
    Text* text_;
    explicit DecoratedText(Text* text) : text_(text) {}
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }

};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::string text2 = data;
        std::reverse(text2.begin(), text2.end());
        text_->render(text2);
    }

};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& data, const std::string& data2) const {
        std::stringstream strm;
        strm << "<a href=" << data << ">" << data2 << "</a>";
        std::string text2 = strm.str();
        text_->render(text2);
    }

};

int main()
{
    auto text_block = new Paragraph(new Text());
    text_block->render("Hello world");

    std::cout << "\n" << std::endl;

    auto text_block2 = new Reversed(new Text());
    text_block2->render("Hello world");

    std::cout << "\n" << std::endl;

    auto text_block3 = new Link(new Text());
    text_block3->render("netology.ru", "Hello world");
}