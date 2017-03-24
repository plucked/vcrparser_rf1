VCR File Parser for rFactor 1
=============

With this software, you can read and write the rFactor 1 replay files. Because those files are not well documented, only a bunch of events can get readed and manipulated. The rest will get handled as unknown event.

Features
=============
* reading and writing the replays (including unzipping and zipping)
* header informations (only few bytes are names as unknown)
* drivers
* cameras
* replay information (length, start, end)
* eventgroups (time and events)
* events:
  * Event Checkpoint (SYS)
  * Event Scoreboard (SYS)
  * Event SFX (no further parsing of information yet)
  * Event VFX (same as SFX)
  * Event ZipLOC (nearly all information, only few bits left, but the important ones like position and orientation)

Contribute
=============

It would be nice if you can code C++ and help to understand the replay format. Its a intention that I don't wrote the parsing with structs, I will let the structure more dynamic for future plans to read the rF2 replays too.

When I tried to figure out, what the structure could be, the 010 Editor was a great help. There is a template for the unzipped replays in the "010 Template" folder. This makes easier to get a human readable form of the binary file.

Building
=============

To build this tool, you need Visual Studio 2012 (or you have to set the VS target manually to your version, its easy to get it working with 2010 or 2008). Because of lazyness, you also have to set the path of your compiled boost library. If you don't have that one, you need to download it here (http://boost.org).

To compile boost you have to follow the next steps:

1. Unzip (o:
2. Run the bootstrap.bat
3. Open the command line utility and browse to this folder (or simply type "cmd" into the location bar of your explorer)
4. Build boost by executing "b2 link=static threading=multi runtime-link=shared" (this will build all libs (even those, which are not used at the moment) as static libraries)
5. You should now have a bunch of libraries in your <boostdir>/stage/lib folder
6. Done 

I don't use the filters in visual studio. Instead I click on the "Show All Files" in the Solution Explorer view to see the actual file structure.
