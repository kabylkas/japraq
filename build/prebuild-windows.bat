:: Copyright (c) 2021 Kabylkas Labs.
:: Licensed under the Apache License, Version 2.0.

:: Generate Visual Studio 2022 Solution files.
mkdir windows
cd windows
cmake -G "Visual Studio 17 2022" ../../
