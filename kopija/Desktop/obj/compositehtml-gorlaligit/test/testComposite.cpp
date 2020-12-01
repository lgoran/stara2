#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>

#include "../src/composite.h"
 
using namespace std;

TEST(Composite, Test1)
{
    std::unique_ptr<HTMLCompositeTag> root{new HTMLCompositeTag("html")};
    root->addComponent(new HTMLCompositeTag("body"));
    auto * body = root->getComponent(0)->getComposite();
    body->addComponent(new HTMLTag("p","Osobna web stranica."));
    body->addComponent(new HTMLCompositeTag("ul"));
    auto * ul = body->getComponent(1)->getComposite();
    ul->addComponent(new HTMLTag("li", "item-1"));
    ul->addComponent(new HTMLTag("li", "item-2")); 
    body->addComponent(new HTMLCompositeTag("p"));
    auto * p = body->getLastComponent()->getComposite();
    p->addComponent(new HTMLText("Ovaj tekst je "));
    p->addComponent(new HTMLTag("strong","pisan podebljano."));



    auto it = root->iterator();
    it.first();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "html");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "body");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "p");
    ASSERT_STREQ(it.currentItem().getBody().c_str(), "Osobna web stranica.");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "ul");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "li");
    ASSERT_STREQ(it.currentItem().getBody().c_str(), "item-1");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "li");
    ASSERT_STREQ(it.currentItem().getBody().c_str(), "item-2");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "p");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "text");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "strong");
    ASSERT_STREQ(it.currentItem().getBody().c_str(), "pisan podebljano.");
    it.next();
    ASSERT_EQ(it.isDone(), true);
}

TEST(Composite, Test2) {
    std::unique_ptr<HTMLCompositeTag> root{new HTMLCompositeTag("html")};
    root->addComponent(new HTMLCompositeTag("body"));
    auto * body = root->getComponent(0)->getComposite();
    body->addComponent(new HTMLTag("p","Osobna web stranica."));
    body->addComponent(new HTMLCompositeTag("ol"));
    auto * ul = body->getComponent(1)->getComposite();
    ul->addComponent(new HTMLTag("li", "oitem-1"));


    auto it = root->iterator();
    it.first();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "html");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "body");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "p");
    ASSERT_STREQ(it.currentItem().getBody().c_str(), "Osobna web stranica.");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "ol");
    it.next();
    ASSERT_STREQ(it.currentItem().getTagName().c_str(), "li");
    ASSERT_STREQ(it.currentItem().getBody().c_str(), "oitem-1");
    it.next();
    ASSERT_EQ(it.isDone(), true);
}

TEST(Composite, Test3) {
     std::unique_ptr<HTMLCompositeTag> root{new HTMLCompositeTag("html")};
     root->addComponent(new HTMLCompositeTag("body"));
     auto body = root->getComponent(0)->getComposite();
     body->addComponent(new HTMLTag("h1","Naslov"));
     body->addComponent(new HTMLCompositeTag("ol"));
     auto ol = body->getComponent(1)->getComposite();
     ol->addComponent(new HTMLTag("li", "oitem-1"));
     ol->addComponent(new HTMLTag("li", "oitem-2"));
     ol->addComponent(new HTMLTag("li", "oitem-3"));

    auto it = root->iterator();
    for(it.first(); !it.isDone(); it.next()){
        auto & xx{it.currentItem()};
        if(xx.getTagName() == "h1")
             xx.setTagName("h2");
    }

    ASSERT_STREQ(body->getComponent(0)->getTagName().c_str(), "h2");

    // Ponovna inicijalizacija istog iteratora.
    for(it.first(); !it.isDone(); it.next()){
        auto & xx{it.currentItem()};
        //std::cout << xx.getTagName() << std::endl;
        if(xx.getTagName() == "ol"){
             xx.getComposite()->removeComponent(0);
             break;
        }
    }
    it = root->iterator(); // CCTor
    body = root->getComponent(0)->getComposite();
    ol = body->getComponent(1)->getComposite();

    ASSERT_STREQ(ol->getComponent(0)->getBody().c_str(), "oitem-2");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
