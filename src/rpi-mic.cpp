// -*- mode: c++; c-basic-offset: 4; encoding: utf-8; -*-

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

        snd_ctl_t *ctl = nullptr;
        rv = snd_ctl_open(&ctl, name, 0);
        if (rv < 0) {
            std::cerr << "Error opening snd_ctl_t: " << rv << std::endl;
            break;
        }

        rv = snd_ctl_close(ctl);
        if (rv < 0) {
            std::cerr << "Error closing snd_ctl_t: " << rv << std::endl;
            break;
        }
    }

    return 0;
}
