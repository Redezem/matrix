/*
-------------------------------
Smith: file preprocessor object
-------------------------------


A Redezrian Production

Copyright 2013 Stefan Prandl

This file is part of Matrix.

    Matrix is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Matrix is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Matrix.  If not, see <http://www.gnu.org/licenses/>.


*/
#pragma once
class Smith{
	private:
	char* TranslationArray; //array to translate between user "characters" and matrix "IDs"
	int numberOfElements; //to keep a track of how big said array is
	void FindNumberOfElements(char*); //uses the node connections sheet to identify the number of elements
	void ConstructTranslationArray(char*); //populates the translation array using the node connections sheet
	char* Translate(char*,char*); //takes in a node conn file and a heuristic file and returns a translated page
	FILE* OpenFile(char*,char*); //nice wrapper for file opening, cause there's a lot of this
	public:
	char* MakeTranslated(char*,char*); //initial tranlsation function
	int WhatIs(char); //post initiation translation function
};
