/*
    Copyright 2019 p-sam
    Copyright 2021 natinusala

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <switch.h>

#include <borealis/core/application.hpp>
#include <borealis/core/logger.hpp>
#include <borealis/platforms/switch/switch_font.hpp>
#include <borealis/core/i18n.hpp>

namespace brls
{

void SwitchFontLoader::loadFonts()
{
    std::string locale = Application::getLocale();
    PlSharedFontType ft = PlSharedFontType_Standard;
    if (locale == LOCALE_ZH_CN || locale == LOCALE_ZH_HANS) {
        ft = PlSharedFontType_ChineseSimplified;
    } else if (locale == LOCALE_ZH_TW || locale == LOCALE_ZH_HANT) {
        ft = PlSharedFontType_ChineseTraditional;
    } else if (locale == LOCALE_Ko) {
        ft = PlSharedFontType_KO;
    }

    PlFontData font;
    Result rc;

    // Standard
    rc = plGetSharedFontByType(&font, ft);
    if (R_SUCCEEDED(rc))
        Application::loadFontFromMemory(FONT_REGULAR, font.address, font.size, false);
    else
        Logger::error("switch: could not load Standard shared font: {:#x}", rc);

    // Extented (symbols)
    rc = plGetSharedFontByType(&font, PlSharedFontType_NintendoExt);
    if (R_SUCCEEDED(rc))
        Application::loadFontFromMemory(FONT_SWITCH_ICONS, font.address, font.size, false);
    else
        Logger::error("switch: could not load Extented shared font: {:#x}", rc);

    // Material icons
    if (!this->loadMaterialFromResources())
        Logger::error("switch: could not load Material icons font from resources", rc);
}

} // namespace brls
