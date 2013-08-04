/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo                           *
 *   massimiliano.torromeo@gmail.com                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef MENU_H
#define MENU_H

#include "link.h"
#include "delegate.h"

#include <string>
#include <vector>

class LinkApp;
class GMenu2X;
class Monitor;
class Surface;

/**
Handles the menu structure

	@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class Menu {
private:
	GMenu2X *gmenu2x;
	Touchscreen &ts;
	int iSection, iLink;
	uint iFirstDispSection, iFirstDispRow;
	std::vector<std::string> sections;
	std::vector< std::vector<Link*> > links;

	void readLinks();
	void freeLinks();
	void orderLinks();

	// Load all the sections of the given "sections" directory.
	void readSections(std::string parentDir);

#ifdef HAVE_LIBOPK
	// Load all the .opk packages of the given directory
	void readPackages(std::string parentDir);
#ifdef ENABLE_INOTIFY
	std::vector<Monitor *> monitors;
#endif
#endif

	// Load all the links on the given section directory.
	void readLinksOfSection(std::string path, std::vector<std::string> &linkfiles);

public:
	Menu(GMenu2X *gmenu2x, Touchscreen &ts);
	~Menu();

#ifdef HAVE_LIBOPK
	void openPackage(std::string path, bool order = true);
	void openPackagesFromDir(std::string path);
#ifdef ENABLE_INOTIFY
	void removePackageLink(std::string path);
#endif
#endif

	std::vector<Link*> *sectionLinks(int i = -1);

	int selSectionIndex();
	const std::string &selSection();
	void decSectionIndex();
	void incSectionIndex();
	void setSectionIndex(int i);
	uint firstDispSection();
	uint firstDispRow();

	bool addActionLink(uint section, const std::string &title,
			function_t action, const std::string &description="",
			const std::string &icon="");
	bool addLink(std::string path, std::string file, std::string section="");
	bool addSection(const std::string &sectionName);
	void deleteSelectedLink();
	void deleteSelectedSection();

	void loadIcons();
	void paint(Surface &s);
	bool linkChangeSection(uint linkIndex, uint oldSectionIndex, uint newSectionIndex);

	int selLinkIndex();
	Link *selLink();
	LinkApp *selLinkApp();
	void linkLeft();
	void linkRight();
	void linkUp();
	void linkDown();
	void setLinkIndex(int i);

	const std::vector<std::string> &getSections() { return sections; }
	void renameSection(int index, const std::string &name);
};

#endif // MENU_H
