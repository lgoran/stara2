#pragma once
#include <vector>
#include <stack>
#include <string>
class HTMLCompositeTag;
class Iterator;
class CompositeIterator;
class HTMLComponent {
public:
  HTMLComponent () {}
  virtual ~HTMLComponent () {}
  virtual inline HTMLCompositeTag *getComposite () { return nullptr; }
  virtual inline std::string getTagName () const { return ""; }
  virtual inline void setTagName (std::string) {}
  virtual inline std::string getStartTag () const { return ""; }
  virtual inline std::string getEndTag () const { return ""; }
  virtual inline std::string getBody () const { return ""; }
  virtual inline void setBody (std::string) {}
  std::string generateHTML ();
  virtual CompositeIterator iterator () const;
};
 
class HTMLTag : public HTMLComponent {
public:
  HTMLTag (std::string tagName = "", std::string body = "") : HTMLComponent(), mTagName(tagName), mBody(body) {}
  inline std::string getTagName () const { return mTagName; }
  inline void setTagName (std::string tagName) { mTagName = tagName; }
  inline std::string getStartTag () const { return "<" + mTagName + ">"; }
  inline std::string getEndTag () const { return "</" + mTagName + ">"; }
  inline std::string getBody () const { return mBody; }
  inline void setBody (std::string body) { mBody = body; }
private:
  std::string mTagName;
  std::string mBody;
};

class HTMLText : public HTMLComponent {
public:
  HTMLText (std::string body = "") : HTMLComponent(), mBody(body) {}
  inline std::string getTagName () const { return "text"; }
  inline std::string getBody () const { return mBody; }
  inline void setBody (std::string body) { mBody = body; }
private:
  std::string mBody;
};

class HTMLCompositeTag : public HTMLComponent {
public: 
  HTMLCompositeTag (std::string tagName = "") : HTMLComponent(), mTagName(tagName), mChildren({ this }) {}
  ~HTMLCompositeTag ();
  inline HTMLCompositeTag *getComposite () { return this; }
  inline std::string getTagName () const { return mTagName; }
  inline void setTagName (std::string tagName) { mTagName = tagName; }
  inline std::string getStartTag () const { return "<" + mTagName + ">"; }
  inline std::string getEndTag () const { return "</" + mTagName + ">"; }
  CompositeIterator iterator ();
  void addComponent (HTMLComponent *cmp);
  void removeComponent (std::size_t index);
  HTMLComponent *getComponent (std::size_t index);
  inline HTMLComponent *getLastComponent () { return mChildren.size() > 1 ? mChildren[mChildren.size() - 1] : nullptr; } 
  inline std::vector<HTMLComponent*>& getChildren () { return mChildren; }
private:
  std::string mTagName;
  std::vector<HTMLComponent*> mChildren;
};
class Iterator {
public:
  Iterator () {}
  Iterator (const Iterator& it) {}
  virtual ~Iterator () {}
  virtual void first () = 0;
  virtual void next () = 0;
  virtual bool isDone () = 0;
  virtual HTMLComponent& currentItem () const = 0;
};
class CompositeIterator : public Iterator {
public:
  CompositeIterator (std::vector<HTMLComponent*>& container) : Iterator(), mContainer(container), pocetak(mContainer.begin()), kraj(mContainer.end()) {}
  CompositeIterator (const CompositeIterator& it) : Iterator(it), stog(it.stog), mContainer(it.mContainer), pocetak(it.pocetak), kraj(it.kraj) {}
  CompositeIterator& operator= (const CompositeIterator& it) {
    if (&it == this) {
      return *this;
    }
    Iterator::operator=(it);
    pocetak = it.pocetak;
    kraj = it.kraj;
    stog = it.stog;
    mContainer = it.mContainer;    
  }
  void first ();
  void next ();
  inline bool isDone () { return stog.empty() && pocetak == kraj; }
  inline HTMLComponent& currentItem () const { return **pocetak; }
private:
  using contIter = std::vector<HTMLComponent*>::iterator;
  std::stack<contIter> stog;
  std::vector<HTMLComponent*>& mContainer;
  contIter pocetak;
  contIter kraj;
};
