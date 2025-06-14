//
// Created by Alex Gomes on 2025-06-11.
//

#include "GifDecoder.h"

GifDecoder::GifDecoder() {
    // Path to GIF file in assets
    std::string gifPath = "../assets/circle.gif";

    int error;
    GifFileType* gif = DGifOpenFileName(gifPath.c_str(), &error);
    if (gif == nullptr) {
        std::cerr << "Failed to open GIF: " << GifErrorString(error) << std::endl;
        return;
    }

    if (DGifSlurp(gif) != GIF_OK) {
        std::cerr << "Failed to read GIF content: " << GifErrorString(gif->Error) << std::endl;
        DGifCloseFile(gif, &error);
        return;
    }

    std::cout << "GIF width: " << gif->SWidth << std::endl;
    std::cout << "GIF height: " << gif->SHeight << std::endl;
    std::cout << "Frame count: " << gif->ImageCount << std::endl;

    for (int i = 0; i < gif->ImageCount; ++i) {
        const SavedImage& frame = gif->SavedImages[i];
        const GifImageDesc& desc = frame.ImageDesc;

        std::cout << "Frame " << i << ": ";
        std::cout << "Position: (" << desc.Left << ", " << desc.Top << "), ";
        std::cout << "Size: " << desc.Width << "x" << desc.Height << std::endl;

        // Pixel data
        const GifByteType* pixels = frame.RasterBits;

        // Optional: access delay using extension blocks
        int delay = 0;
        for (int j = 0; j < frame.ExtensionBlockCount; ++j) {
            const ExtensionBlock& ext = frame.ExtensionBlocks[j];
            if (ext.Function == GRAPHICS_EXT_FUNC_CODE && ext.ByteCount >= 4) {
                delay = (ext.Bytes[2] << 8) | ext.Bytes[1];  // in hundredths of a second
                break;
            }
        }

        std::cout << "  Delay: " << delay * 10 << " ms" << std::endl;
    }

    // Clean up
    if (DGifCloseFile(gif, &error) != GIF_OK) {
        std::cerr << "Failed to close GIF: " << GifErrorString(error) << std::endl;
        return 1;
    }
}
