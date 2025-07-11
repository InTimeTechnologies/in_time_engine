#include "InTimeEditor.h"

// class InTimeEditor

// Static | private
it::InTimeEditor* it::InTimeEditor::singleton = nullptr;

// Getters
it::InTimeEditor* it::InTimeEditor::getSingleton() {
	return singleton;
}

// Object | public

// Constructor / Destructor
it::InTimeEditor::InTimeEditor() {
	if (singleton == nullptr)
		singleton = this;
}
it::InTimeEditor::~InTimeEditor() {
	if (singleton == this)
		singleton = nullptr;
}

// Functions
void it::InTimeEditor::update() {
	hierarchy.update();
	inspector.update();
}
