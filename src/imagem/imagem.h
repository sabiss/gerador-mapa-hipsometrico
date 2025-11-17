Class Imagem{

public:
    int obterLargura(const Pixel& pixel) const;
    int obterAltura(const Pixel& pixel) const;
    bool lerPPM(const std::string filename);
    bool salvarPPM(const std::string filename);

}