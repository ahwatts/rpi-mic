// -*- mode: c++; c-basic-offset: 4; encoding: utf-8; -*-

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <alsa/asoundlib.h>

int main(int, char**) {
    // snd_ctl_t *ctl;

    // int rv = snd_ctl_open(&ctl, "test", SND_CTL_NONBLOCK);
    // std::cout << "rv = " << rv << std::endl;
    // snd_ctl_close(ctl);

    int card = -1;

    while (true) {
        int rv = 0;

        rv = snd_card_next(&card);
        if (rv < 0) {
            std::cerr << "Error determining next sound card: " << rv << std::endl;
            break;
        }

        if (card < 0) {
            break;
        }

        std::cout << "Found card index: " << card << std::endl;
        char *name, *longname;
        rv = snd_card_get_name(card, &name);
        if (rv < 0) {
            std::cerr << "Error determining the name of sound card: " << card << ": " << rv << std::endl;
            break;
        }
        std::cout << "    Name: " << name << std::endl;

        rv = snd_card_get_longname(card, &longname);
        if (rv < 0) {
            std::cerr << "Error determining the long name of sound card: " << card << ": " << rv << std::endl;
            break;
        }
        std::cout << "    Long Name: " << longname << std::endl;

        void **hints;
        rv = snd_device_name_hint(card, "pcm", &hints);
        if (rv < 0) {
            std::cerr << "Error getting device name hints: " << rv << std::endl;
            break;
        }

        int hint_index = 0;
        while (hints[hint_index] != nullptr) {
            char *name = snd_device_name_get_hint(hints[hint_index], "NAME");
            char *desc = snd_device_name_get_hint(hints[hint_index], "DESC");
            char *ioid = snd_device_name_get_hint(hints[hint_index], "IOID");

            std::replace(desc, desc + std::strlen(desc), '\n', ' ');

            std::cout << "    PCM Device " << name << "\n";
            std::cout << "        Description: " << desc << "\n";
            if (ioid != nullptr) {
                std::cout << "        IOID: " << ioid << std::endl;
            } else {
                std::cout << "        IOID: NULL (both)" << std::endl;
            }

            std::free(name);
            std::free(desc);
            std::free(ioid);
            hint_index += 1;
        }

        rv = snd_device_name_free_hint(hints);
        if (rv < 0) {
            std::cerr << "Error freeing device name hints: " << rv << std::endl;
            break;
        }
    }

    return 0;
}
