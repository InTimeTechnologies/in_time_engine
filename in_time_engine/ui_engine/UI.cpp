#include "UI.h"

// class UI

// Static | private

// Properties
std::list<it::UI*> it::UI::s_uiList = std::list<it::UI*>();

// Static | public

// Getters
std::list<it::UI*> it::UI::s_getUIList() {
	return s_uiList;
}

// Object | public

// Constructor / Destructor
it::UI::UI() {
	s_uiList.push_back(this);
	node = std::prev(s_uiList.end());
}
it::UI::~UI() {
	s_uiList.erase(node);
}

// Functions
void it::UI::render() {

}
