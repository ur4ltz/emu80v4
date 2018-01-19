/*
 *  Emu80 v. 4.x
 *  © Viktor Pykhonin <pyk@mail.ru>, 2016-2018
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef APOGEY_H
#define APOGEY_H


#include "PlatformCore.h"
#include "RkRomDisk.h"
#include "Crt8275Renderer.h"

class SoundSource;


class ApogeyCore : public PlatformCore
{
    public:
        ApogeyCore();
        virtual ~ApogeyCore();

        bool setProperty(const std::string& propertyName, const EmuValuesList& values) override;

        void draw() override;

        void vrtc(bool isActive) override;
        void inte(bool isActive) override;

        void attachCrtRenderer(Crt8275Renderer* crtRenderer);

    private:
        Crt8275Renderer* m_crtRenderer = nullptr;
        SoundSource* m_beepSoundSource;
        //Pit8253SoundSource* m_pitSoundSource;
};


class ApogeyRenderer : public Crt8275Renderer
{
    public:
        ApogeyRenderer();

        bool setProperty(const std::string& propertyName, const EmuValuesList& values) override;
        std::string getPropertyStringValue(const std::string& propertyName) override;
        void toggleColorMode() override;

    protected:
        const uint8_t* getCurFontPtr(bool gpa0, bool gpa1, bool hglt) override;
        const uint8_t* getAltFontPtr(bool gpa0, bool gpa1, bool hglt) override;
        uint32_t getCurFgColor(bool gpa0, bool gpa1, bool hglt) override;
        uint32_t getCurBgColor(bool gpa0, bool gpa1, bool hglt) override;

    private:
        bool m_colorMode = true;
        void setColorMode(bool colorMode);
};


class ApogeyRomDisk : public RkRomDisk
{
    public:
        ApogeyRomDisk(std::string romDiskName);
        uint8_t getPortA() override;
        void setPortB(uint8_t value) override;
        void setPortC(uint8_t value) override;
    private:
        bool m_oldA15 = false;
};

#endif // APOGEY_H
