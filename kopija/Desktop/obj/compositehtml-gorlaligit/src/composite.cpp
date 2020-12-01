#include "composite.h"
using namespace std;

string HTMLComponent::generateHTML () {
  string pomocni;
  pomocni.append(getStartTag());  
  if (auto composite = getComposite()) {
    pomocni.append("\n");
    auto& children = composite->getChildren();
    for (int i = 1; i < children.size(); i++)
      pomocni.append(children[i]->generateHTML());
  } 
  else {
    pomocni.append(getBody());
  }
  pomocni.append(getEndTag());
  pomocni.append("\n");
  return pomocni;
}

CompositeIterator HTMLComponent::iterator () const { 
  throw "Greska.Nema iteratora"; 
}

HTMLCompositeTag::~HTMLCompositeTag () {
  for (int i = 1; i < mChildren.size(); i++)
    delete mChildren[i];
  mChildren.clear();
}

void HTMLCompositeTag::addComponent (HTMLComponent *cmp) {
  mChildren.push_back(cmp);
  return;
}

void HTMLCompositeTag::removeComponent (size_t index) {
  if (index < 0 || index >= mChildren.size() - 1) return;
  auto djete = mChildren[index + 1];
  mChildren.erase(mChildren.begin() + index + 1);
  delete djete;
  return;
}

HTMLComponent *HTMLCompositeTag::getComponent (size_t index) {
  if (index < 0 || index >= mChildren.size() - 1) return nullptr;  
  return mChildren[index + 1];
}
void CompositeIterator::first () {
  pocetak = mContainer.begin();
  stog = stack<CompositeIterator::contIter>();
  return;
}
void CompositeIterator::next () {
  if (pocetak == kraj && stog.empty()) {
    return;
  }
  if (pocetak == mContainer.begin()) {
    ++pocetak;
    return;
  }
  if (auto composite = (*pocetak)->getComposite()) {
    auto& container = composite->getChildren();
    stog.push(pocetak);
    stog.push(kraj);
    pocetak = container.begin();
    ++pocetak;
    kraj = container.end();
    return;
  }  
  ++pocetak;
  while (!stog.empty() && pocetak == kraj) {
    kraj = stog.top();
    stog.pop();
    pocetak = stog.top();
    stog.pop();
    ++pocetak;
  }
  return;
}
CompositeIterator HTMLCompositeTag::iterator () { 
  return CompositeIterator(mChildren); 
}