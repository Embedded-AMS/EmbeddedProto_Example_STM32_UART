::
:: Copyright (C) 2020-2021 Embedded AMS B.V. - All Rights Reserved
::
:: This file is part of Embedded Proto.
::
:: Embedded Proto is open source software: you can redistribute it and/or 
:: modify it under the terms of the GNU General Public License as published 
:: by the Free Software Foundation, version 3 of the license.
::
:: Embedded Proto  is distributed in the hope that it will be useful,
:: but WITHOUT ANY WARRANTY; without even the implied warranty of
:: MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
:: GNU General Public License for more details.
::
:: You should have received a copy of the GNU General Public License
:: along with Embedded Proto. If not, see <https://www.gnu.org/licenses/>.
::
:: For commercial and closed source application please visit:
:: <https://EmbeddedProto.com/license/>.
::
:: Embedded AMS B.V.
:: Info:
::   info at EmbeddedProto dot com
::
:: Postal address:
::   Johan Huizingalaan 763a
::   1066 VH, Amsterdam
::   the Netherlands
::

:: This script will perform various actions to setup everything to get you started with this example

:: Setup the submodule embedded proto
cd EmbeddedProto
call setup.bat
cd ..

:: Setup the virtual environment for the desktop Python script.
cd desktop
python -m venv venv
call .\venv\Scripts\activate.bat & pip install -r requirements.txt & call .\venv\Scripts\deactivate.bat
cd ..

:: Generate the source code based on the *.proto files.
call generate_source_files.bat
