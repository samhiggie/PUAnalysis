/*
 * float weightMuTau(float pt1,float eta1) {
 *   return muHTTID(pt1,eta1)*muHTTISO(pt1,eta1);
 *
 *   }
 *
 *
 *
 *   float weightETau(float pt1,float eta1) {
 *     return eHTTID(pt1,eta1)*eHTTISO(pt1,eta1);
 *     }
 *
 *    //float eHTTID(float probe_Ele_pt, float probe_Ele_abseta, bool passingHTTID=true, Variation variation=Variation::CENTRAL) {
 */

enum Variation {
    CENTRAL,
    STAT_UP,
    STAT_DOWN,
    SYST_ALT_TEMPL,
    SYST_TAG_PT30,
    SYST_CMSSHAPE,
    EFF_DATA,
    EFF_DATA_ERRSYM,
    EFF_MC,
    EFF_MC_ERRSYM,
};

float mHTTID(float probe_pt, float probe_abseta, bool passingHTTIDICHEP=true, Variation variation=Variation::CENTRAL){
    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.985142;
    if ( variation == Variation::STAT_UP && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.989499;
    if ( variation == Variation::CENTRAL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.985149;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.002635;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.981264;
    if ( variation == Variation::EFF_MC && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.991597;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.001469;
    if ( variation == Variation::EFF_DATA && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.976871;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.984653;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.982917;
    if ( variation == Variation::STAT_UP && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.990563;
    if ( variation == Variation::CENTRAL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.982961;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.004127;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.976407;
    if ( variation == Variation::EFF_MC && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.983979;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.002881;
    if ( variation == Variation::EFF_DATA && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.967212;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.982668;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.993063;
    if ( variation == Variation::STAT_UP && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.996424;
    if ( variation == Variation::CENTRAL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.993063;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.002342;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.989773;
    if ( variation == Variation::EFF_MC && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.994442;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000971;
    if ( variation == Variation::EFF_DATA && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.987544;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.993089;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.995656;
    if ( variation == Variation::STAT_UP && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.998681;
    if ( variation == Variation::CENTRAL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.995669;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.001974;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.992545;
    if ( variation == Variation::EFF_MC && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.993217;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.001078;
    if ( variation == Variation::EFF_DATA && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.988915;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.995646;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.988820;
    if ( variation == Variation::STAT_UP && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.992798;
    if ( variation == Variation::CENTRAL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.988822;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.002907;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.984767;
    if ( variation == Variation::EFF_MC && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.993459;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.001094;
    if ( variation == Variation::EFF_DATA && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.982354;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.989134;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.995376;
    if ( variation == Variation::STAT_UP && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 1.001072;
    if ( variation == Variation::CENTRAL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.995359;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.004420;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.990094;
    if ( variation == Variation::EFF_MC && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.993529;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.001037;
    if ( variation == Variation::EFF_DATA && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.988918;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.995602;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 1.000170;
    if ( variation == Variation::STAT_UP && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 1.008919;
    if ( variation == Variation::CENTRAL && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.999710;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.008309;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.989778;
    if ( variation == Variation::EFF_MC && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.992519;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.001189;
    if ( variation == Variation::EFF_DATA && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.992231;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 1.000382;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.965394;
    if ( variation == Variation::STAT_UP && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.965642;
    if ( variation == Variation::CENTRAL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.959104;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.005193;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.952882;
    if ( variation == Variation::EFF_MC && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.978471;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.001094;
    if ( variation == Variation::EFF_DATA && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.938455;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.967628;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.972850;
    if ( variation == Variation::STAT_UP && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.980249;
    if ( variation == Variation::CENTRAL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.972867;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.005264;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.965652;
    if ( variation == Variation::EFF_MC && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.968206;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.001852;
    if ( variation == Variation::EFF_DATA && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.941936;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.975804;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.975499;
    if ( variation == Variation::STAT_UP && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.980255;
    if ( variation == Variation::CENTRAL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.975464;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.003994;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.970761;
    if ( variation == Variation::EFF_MC && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.984528;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000696;
    if ( variation == Variation::EFF_DATA && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.960372;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.976541;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.971156;
    if ( variation == Variation::STAT_UP && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.975304;
    if ( variation == Variation::CENTRAL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.971137;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.003462;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.966951;
    if ( variation == Variation::EFF_MC && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.982680;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.000661;
    if ( variation == Variation::EFF_DATA && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.954317;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.968877;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.964628;
    if ( variation == Variation::STAT_UP && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.972568;
    if ( variation == Variation::CENTRAL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.964643;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.006791;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.956627;
    if ( variation == Variation::EFF_MC && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.962693;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.000915;
    if ( variation == Variation::EFF_DATA && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.928655;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.957745;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.972764;
    if ( variation == Variation::STAT_UP && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.981608;
    if ( variation == Variation::CENTRAL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.972696;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.007855;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.963748;
    if ( variation == Variation::EFF_MC && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.964002;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.000775;
    if ( variation == Variation::EFF_DATA && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.937681;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.971002;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.928460;
    if ( variation == Variation::STAT_UP && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.945323;
    if ( variation == Variation::CENTRAL && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.943254;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.001502;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.941188;
    if ( variation == Variation::EFF_MC && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.978505;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.000552;
    if ( variation == Variation::EFF_DATA && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.922978;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.937708;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.979563;
    if ( variation == Variation::STAT_UP && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.980878;
    if ( variation == Variation::CENTRAL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.979899;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.000690;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.978933;
    if ( variation == Variation::EFF_MC && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.990471;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.000279;
    if ( variation == Variation::EFF_DATA && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.970562;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.978541;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.969115;
    if ( variation == Variation::STAT_UP && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.975019;
    if ( variation == Variation::CENTRAL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.969639;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.002913;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.968054;
    if ( variation == Variation::EFF_MC && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.983177;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.000525;
    if ( variation == Variation::EFF_DATA && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.953327;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.968756;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.984221;
    if ( variation == Variation::STAT_UP && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.984651;
    if ( variation == Variation::CENTRAL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.984085;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000381;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.983518;
    if ( variation == Variation::EFF_MC && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.993959;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000185;
    if ( variation == Variation::EFF_DATA && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.978140;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.983636;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.985820;
    if ( variation == Variation::STAT_UP && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.986451;
    if ( variation == Variation::CENTRAL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.985877;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.000372;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.985305;
    if ( variation == Variation::EFF_MC && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.993525;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.000201;
    if ( variation == Variation::EFF_DATA && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.979493;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.985431;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.983306;
    if ( variation == Variation::STAT_UP && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.984296;
    if ( variation == Variation::CENTRAL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.983342;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.000691;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.982394;
    if ( variation == Variation::EFF_MC && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.990233;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.000255;
    if ( variation == Variation::EFF_DATA && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.973738;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.982979;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.988498;
    if ( variation == Variation::STAT_UP && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.989453;
    if ( variation == Variation::CENTRAL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.988603;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.000633;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.987760;
    if ( variation == Variation::EFF_MC && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.991988;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.000209;
    if ( variation == Variation::EFF_DATA && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.980682;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.988285;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.969416;
    if ( variation == Variation::STAT_UP && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.965036;
    if ( variation == Variation::CENTRAL && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.964489;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.000394;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.963948;
    if ( variation == Variation::EFF_MC && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.995077;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.000153;
    if ( variation == Variation::EFF_DATA && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.959741;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.973418;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.980527;
    if ( variation == Variation::STAT_UP && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.980757;
    if ( variation == Variation::CENTRAL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.980506;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.000089;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.980260;
    if ( variation == Variation::EFF_MC && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.991380;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.000161;
    if ( variation == Variation::EFF_DATA && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.972054;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.979905;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.972841;
    if ( variation == Variation::STAT_UP && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.973475;
    if ( variation == Variation::CENTRAL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.972845;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.000402;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.972057;
    if ( variation == Variation::EFF_MC && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.984903;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.000304;
    if ( variation == Variation::EFF_DATA && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.958158;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.972110;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.986337;
    if ( variation == Variation::STAT_UP && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.987084;
    if ( variation == Variation::CENTRAL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.986804;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000178;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.986526;
    if ( variation == Variation::EFF_MC && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.995355;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000101;
    if ( variation == Variation::EFF_DATA && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.982220;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.986042;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.986803;
    if ( variation == Variation::STAT_UP && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.987139;
    if ( variation == Variation::CENTRAL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.986789;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.000235;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.986440;
    if ( variation == Variation::EFF_MC && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.994784;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.000114;
    if ( variation == Variation::EFF_DATA && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.981642;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.986664;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.985315;
    if ( variation == Variation::STAT_UP && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.985738;
    if ( variation == Variation::CENTRAL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.985311;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.000290;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.984887;
    if ( variation == Variation::EFF_MC && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.993777;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.000135;
    if ( variation == Variation::EFF_DATA && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.979179;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.984633;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.990147;
    if ( variation == Variation::STAT_UP && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.990379;
    if ( variation == Variation::CENTRAL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.990143;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.000202;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.989753;
    if ( variation == Variation::EFF_MC && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.995128;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.000111;
    if ( variation == Variation::EFF_DATA && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.985320;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.989949;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.984484;
    if ( variation == Variation::STAT_UP && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.984770;
    if ( variation == Variation::CENTRAL && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.984484;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.000201;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.984199;
    if ( variation == Variation::EFF_MC && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.996908;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.000085;
    if ( variation == Variation::EFF_DATA && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.981439;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.983693;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.982236;
    if ( variation == Variation::STAT_UP && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.982716;
    if ( variation == Variation::CENTRAL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.982327;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.000229;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.981942;
    if ( variation == Variation::EFF_MC && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.991613;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.000157;
    if ( variation == Variation::EFF_DATA && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.974088;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.981630;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.974093;
    if ( variation == Variation::STAT_UP && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.974843;
    if ( variation == Variation::CENTRAL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.974102;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.000429;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.973371;
    if ( variation == Variation::EFF_MC && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.984361;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.000303;
    if ( variation == Variation::EFF_DATA && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.958868;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.973590;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.987623;
    if ( variation == Variation::STAT_UP && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.987918;
    if ( variation == Variation::CENTRAL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.987645;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000177;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.987373;
    if ( variation == Variation::EFF_MC && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.995495;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000095;
    if ( variation == Variation::EFF_DATA && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.983195;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.987206;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.988558;
    if ( variation == Variation::STAT_UP && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.988825;
    if ( variation == Variation::CENTRAL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.988553;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.000168;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.988284;
    if ( variation == Variation::EFF_MC && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.994967;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.000102;
    if ( variation == Variation::EFF_DATA && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.983578;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.988392;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.986692;
    if ( variation == Variation::STAT_UP && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.987040;
    if ( variation == Variation::CENTRAL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.986384;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.000544;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.985729;
    if ( variation == Variation::EFF_MC && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.994619;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.000109;
    if ( variation == Variation::EFF_DATA && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.981076;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.986507;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.991392;
    if ( variation == Variation::STAT_UP && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.992151;
    if ( variation == Variation::CENTRAL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.991226;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.000833;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.990306;
    if ( variation == Variation::EFF_MC && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.996131;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.000086;
    if ( variation == Variation::EFF_DATA && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.987391;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.991276;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.985042;
    if ( variation == Variation::STAT_UP && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.985340;
    if ( variation == Variation::CENTRAL && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.985054;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.000217;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.984762;
    if ( variation == Variation::EFF_MC && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.997461;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.000072;
    if ( variation == Variation::EFF_DATA && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.982553;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.984503;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.983780;
    if ( variation == Variation::STAT_UP && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.984079;
    if ( variation == Variation::CENTRAL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.983562;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.000239;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.983056;
    if ( variation == Variation::EFF_MC && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.991150;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.000272;
    if ( variation == Variation::EFF_DATA && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.974857;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIDICHEP) ) return 0.981906;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.976113;
    if ( variation == Variation::STAT_UP && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.979720;
    if ( variation == Variation::CENTRAL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.976117;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.001839;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.974946;
    if ( variation == Variation::EFF_MC && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.983883;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.000521;
    if ( variation == Variation::EFF_DATA && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.960385;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIDICHEP) ) return 0.973860;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.988726;
    if ( variation == Variation::STAT_UP && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.989110;
    if ( variation == Variation::CENTRAL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.988662;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000284;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.988222;
    if ( variation == Variation::EFF_MC && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.995458;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.000161;
    if ( variation == Variation::EFF_DATA && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.984171;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIDICHEP) ) return 0.987122;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.989119;
    if ( variation == Variation::STAT_UP && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.989659;
    if ( variation == Variation::CENTRAL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.989116;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.000364;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.988578;
    if ( variation == Variation::EFF_MC && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.994674;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.000176;
    if ( variation == Variation::EFF_DATA && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.983848;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIDICHEP) ) return 0.987854;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.982697;
    if ( variation == Variation::STAT_UP && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.983313;
    if ( variation == Variation::CENTRAL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.982691;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.000410;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.982079;
    if ( variation == Variation::EFF_MC && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.993058;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.000206;
    if ( variation == Variation::EFF_DATA && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.975869;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIDICHEP) ) return 0.980486;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.987533;
    if ( variation == Variation::STAT_UP && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.988143;
    if ( variation == Variation::CENTRAL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.987358;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.000587;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.986579;
    if ( variation == Variation::EFF_MC && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.992835;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.000192;
    if ( variation == Variation::EFF_DATA && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.980284;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIDICHEP) ) return 0.984232;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.983008;
    if ( variation == Variation::STAT_UP && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.983282;
    if ( variation == Variation::CENTRAL && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.982774;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.000364;
    if ( variation == Variation::STAT_DOWN && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.982270;
    if ( variation == Variation::EFF_MC && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.996341;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.000143;
    if ( variation == Variation::EFF_DATA && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.979178;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIDICHEP) ) return 0.977803;

    return 1.; // Default
} 

float mHTTISO(float probe_pt, float probe_abseta, bool passingHTTIso=true, bool passingHTTIDICHEP=true, Variation variation=Variation::CENTRAL)  {
    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 1.013509;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 1.017743;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 1.013531;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.001595;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 1.009459;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.975201;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.002411;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.988396;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 1.013619;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 1.004511;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 1.010160;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 1.004500;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.002648;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.998712;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.982663;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.002964;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.987085;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 1.003915;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 1.002952;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 1.006169;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 1.002946;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.001580;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.999894;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.985749;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.001508;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.988653;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 1.002533;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 1.007801;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 1.011353;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 1.007796;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.001624;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 1.004401;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.980723;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.001771;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.988368;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 1.007487;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 1.003301;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 1.006798;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 1.003285;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.001481;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 1.000233;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.982743;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.001738;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.985971;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 1.003531;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 1.005948;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 1.008883;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 1.005941;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.001370;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 1.002969;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.984761;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.001533;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.990611;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 1.005820;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 1.003651;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 1.006439;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 1.003648;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.001208;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 1.000998;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.988062;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.001474;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.991666;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=100 && probe_pt<1000 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 1.003466;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.956341;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.970726;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.956456;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.005100;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.943870;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.636504;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.003600;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.608789;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.958458;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.970620;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 1.031820;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.970401;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.020288;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.952698;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.639592;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.005053;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.620661;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.968507;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.944261;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.952951;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.944530;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.003184;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.936343;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.679842;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.002606;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.642131;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.943157;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.966712;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.973856;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.966721;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.005278;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.952805;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.710666;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.002286;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.687015;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.965741;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.970822;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.983617;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.970235;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.007218;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.958123;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.731205;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.002166;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.709441;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.971355;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.967720;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.972023;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.967734;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.001603;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.963501;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.775288;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.001757;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.750273;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.969207;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.961398;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.965500;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.961396;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.001862;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.957354;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.810417;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.001496;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.779132;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=10 && probe_pt<20 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.963789;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.970010;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.964287;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.961868;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.000969;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.959447;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.828037;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.001076;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.796462;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.969623;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.961105;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.965112;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.961081;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.001877;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.957079;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.831910;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.001524;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.799534;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.962768;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.970634;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.972617;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.970675;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.000777;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.968732;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.837470;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.000875;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.812911;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.971145;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.982102;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.987572;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.981948;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.003851;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.976341;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.843317;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.000901;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.828094;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.982750;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.985396;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.987480;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.985511;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.000774;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.983546;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.852666;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.000916;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.840311;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.986902;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.989058;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.989538;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.987884;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.000665;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.986275;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.874997;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.000772;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.864396;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.990560;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.986031;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.988379;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.986808;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.000774;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.985252;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.901768;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.000645;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.889872;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=20 && probe_pt<30 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.985882;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.981794;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.982734;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.982020;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.000227;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.981311;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.930078;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.000443;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.913356;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.981819;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.983172;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.984392;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.982791;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.000858;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.981189;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.929354;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.000641;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.913361;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.983092;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.985580;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.986343;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.985579;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.000342;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.984814;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.930893;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.000375;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.917469;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.985422;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.990155;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.991019;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.990248;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.000326;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.989477;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.932327;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.000396;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.923235;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.989693;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.993263;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.994220;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.993218;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.000516;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.992218;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.934329;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.000422;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.927993;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.993477;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.995237;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.996055;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.995312;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.000343;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.994572;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.945602;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.000360;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.941168;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.994794;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.995495;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.996021;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.995428;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.000264;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.994837;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.958286;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.000304;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.953904;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=30 && probe_pt<40 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.995373;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.989080;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.989526;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.988965;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.000255;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.988407;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.970608;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.000291;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.959897;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.988506;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.991482;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.992339;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.991487;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.000408;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.990642;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.970082;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.000419;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.961824;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.991559;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.991290;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.991816;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.991343;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.000232;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.990869;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.972545;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.000231;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.964125;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.990782;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.993432;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.993868;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.993427;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.000203;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.992992;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.974743;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.000225;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.968337;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.993212;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.995436;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.995947;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.995421;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.000288;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.994897;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.976468;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.000225;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.971996;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.994682;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.997173;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.997929;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.997201;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.000526;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.996476;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.981331;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.000188;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.978584;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.996977;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.996889;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.997251;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.996927;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.000148;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.996605;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.985428;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.000171;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.982400;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=40 && probe_pt<50 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.997098;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.993878;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.994670;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.993886;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.000369;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.993114;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.981004;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.000397;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.975006;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.0 && probe_abseta<0.2 && passingHTTIso) ) return 0.994409;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.995543;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.996780;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.995540;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.000639;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.994327;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.981135;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.000567;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.976760;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.2 && probe_abseta<0.3 && passingHTTIso) ) return 0.995344;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.994823;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.995409;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.994709;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.000376;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.994006;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.982036;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.000315;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.976840;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.3 && probe_abseta<0.6 && passingHTTIso) ) return 0.994808;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.996889;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.997636;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.997033;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.000277;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.996441;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.982967;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.000312;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.980051;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.6 && probe_abseta<0.9 && passingHTTIso) ) return 0.996561;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.998543;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.999146;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.998555;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.000268;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.997970;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.983948;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.000311;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.982526;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=0.9 && probe_abseta<1.2 && passingHTTIso) ) return 0.998580;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.998094;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.998596;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.998107;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.000228;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.997619;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.987314;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.000255;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.985445;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.2 && probe_abseta<1.6 && passingHTTIso) ) return 0.998238;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.998489;
    if ( variation == Variation::STAT_UP && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.998931;
    if ( variation == Variation::CENTRAL && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.998461;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.000221;
    if ( variation == Variation::STAT_DOWN && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.998002;
    if ( variation == Variation::EFF_MC && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.989574;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.000239;
    if ( variation == Variation::EFF_DATA && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.988051;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTIDICHEP && probe_pt>=50 && probe_pt<100 && probe_abseta>=1.6 && probe_abseta<2.1 && passingHTTIso) ) return 0.998718;

    return 1.; // Default
} 


float eHTTID(float probe_Ele_pt, float probe_Ele_abseta, bool passingHTTID=true, Variation variation=Variation::CENTRAL){
    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.993249;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.999673;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.993450;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.003460;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.987413;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.922206;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.002206;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.916165;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.994107;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.975583;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.985013;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.975604;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.005197;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.966273;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.886984;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.003192;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.865345;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.977080;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.986155;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.999488;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.985258;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.007687;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.971623;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.891102;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.004794;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.877966;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.985644;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 1.002413;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 1.058874;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 1.001904;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.032812;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.946774;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.851127;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.014840;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.852748;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.999947;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.984152;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 1.001554;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.993746;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.003018;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.986015;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.623623;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.001839;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.619723;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.986807;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.969373;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.982186;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.967159;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.007081;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.952280;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.589999;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.001800;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.570623;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.976734;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.863870;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.880565;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.863905;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.008353;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.847490;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.608629;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.001982;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.525797;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.898482;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.874954;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.907119;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.874617;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.015346;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.843984;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.609672;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.004455;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.533230;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.899035;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.976884;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.979547;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.976999;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.001357;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.974463;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.797043;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.000685;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.778710;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.973732;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.958885;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.962952;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.958854;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.002331;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.954771;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.762380;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.000821;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.731011;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.957461;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.911451;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.915181;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.911426;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.001927;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.907690;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.759365;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.001006;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.692105;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.909064;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.923857;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.935317;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.923559;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.006677;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.911833;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.754237;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.002359;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.696583;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.924882;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.977396;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.980925;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.979768;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.000644;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.978613;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.859768;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.000357;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.842373;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.977417;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.971564;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.972309;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.971016;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.000612;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.969729;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.831728;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.000474;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.807621;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.972024;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.953680;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.958768;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.956578;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.001191;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.954391;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.826808;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.000647;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.790906;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.952479;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.960272;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.970438;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.965068;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.002819;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.959747;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.813006;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.001582;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.784606;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.961448;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.980379;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.981315;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.980404;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.000513;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.979495;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.889015;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.000302;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.871594;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.979709;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.976560;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.977843;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.976543;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.000775;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.975183;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.870259;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.000391;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.849845;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.976917;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.970593;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.972580;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.970532;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.001188;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.968483;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.859976;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.000591;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.834634;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.969417;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.975448;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.980891;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.975449;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.003059;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.970018;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.842558;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.001560;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.821872;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.975241;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.984398;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.976531;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.975675;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.000293;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.974822;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.901195;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.000489;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.879274;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTID) ) return 0.984346;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.978139;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.980398;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.978147;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.001218;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.976249;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.883995;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.000630;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.864677;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTID) ) return 0.978050;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.978466;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.998979;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.978927;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.017215;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.957366;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.872333;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.000956;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.853950;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTID) ) return 0.979783;

    if ( variation == Variation::SYST_ALT_TEMPL && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.975690;
    if ( variation == Variation::STAT_UP && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.985389;
    if ( variation == Variation::CENTRAL && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.975727;
    if ( variation == Variation::EFF_DATA_ERRSYM && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.005737;
    if ( variation == Variation::STAT_DOWN && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.966100;
    if ( variation == Variation::EFF_MC && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.858259;
    if ( variation == Variation::EFF_MC_ERRSYM && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.002603;
    if ( variation == Variation::EFF_DATA && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.837426;
    if ( variation == Variation::SYST_CMSSHAPE && (probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTID) ) return 0.976075;

    return 1.; // Default
} 


float eHTTISO(float probe_Ele_pt, float probe_Ele_abseta, bool passingHTTISO=true, bool passingHTTID=true, Variation variation=Variation::CENTRAL){
    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 1.005060;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 1.007692;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 1.005084;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.001509;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 1.002430;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.984607;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.001075;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.989612;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 1.004827;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.996149;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.999745;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.996153;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.002261;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.992569;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.986257;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.001282;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.982463;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.996236;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.999903;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.006919;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.000684;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.003986;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.994580;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.984678;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.002087;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.985351;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.999731;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.010014;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.020281;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.010014;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.002234;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.004539;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.990085;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.005473;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.000000;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=100 && probe_Ele_pt<1000 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.010014;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.969622;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.978253;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.969618;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.004406;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.961001;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.746314;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.002095;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.723640;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.976325;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.969237;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.976314;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.969183;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.003525;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.962120;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.770839;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.002007;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.747084;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.974524;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.978824;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.986090;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.978926;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.003653;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.971843;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.799728;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.002088;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.782874;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.978447;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.985333;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.022878;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.985918;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.017894;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.967655;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.813340;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.004583;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.801887;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=10 && probe_Ele_pt<20 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.983197;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.986260;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.986095;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.983989;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.001140;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.981892;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.856049;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.000670;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.842343;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.990016;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.988622;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.991156;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.988628;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.001418;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.986173;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.867121;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.000751;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.857260;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.989300;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.987477;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.991079;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.988006;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.001763;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.984968;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.870538;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.000908;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.860097;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.989425;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.997397;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.005363;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.999355;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.003422;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.993401;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.895719;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.001936;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.895141;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=20 && probe_Ele_pt<30 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.997174;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.990376;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.992156;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.990980;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.000817;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.989808;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.931860;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.000280;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.923455;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.990432;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.993399;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.993816;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.992776;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.000613;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.991742;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.930397;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.000354;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.923676;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.993755;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.000977;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.002701;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.000610;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.001428;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.998526;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.923653;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.000500;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.924217;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.001406;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.991920;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.995528;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.992567;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.001792;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.989608;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.946543;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.001017;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.939507;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=30 && probe_Ele_pt<40 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.992018;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.994709;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.995169;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.994662;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.000309;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.994157;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.967259;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.000182;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.962096;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.994213;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.997140;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.997803;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.997149;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.000409;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.996498;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.967307;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.000222;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.964550;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.996873;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.998667;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.999227;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.998335;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.000496;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.997447;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.960311;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.000360;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.958712;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.998711;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.998006;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.000459;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.998069;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.001537;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.995747;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.973342;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.000758;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.971463;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=40 && probe_Ele_pt<50 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.998093;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.995972;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.997113;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.995971;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.000679;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.995215;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.978640;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.000251;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.974697;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.0 && probe_Ele_abseta<0.8 && passingHTTISO) ) return 0.996245;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.998080;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.998992;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.998073;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.000610;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.997132;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.979041;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.000301;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.977154;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=0.8 && probe_Ele_abseta<1.479 && passingHTTISO) ) return 0.997923;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.000145;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.004567;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.000153;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.002350;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.998622;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.969392;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.000531;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 0.969540;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=1.479 && probe_Ele_abseta<2.0 && passingHTTISO) ) return 1.000420;

    if ( variation == Variation::SYST_ALT_TEMPL && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.997911;
    if ( variation == Variation::STAT_UP && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 1.000987;
    if ( variation == Variation::CENTRAL && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.997965;
    if ( variation == Variation::EFF_DATA_ERRSYM && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.002014;
    if ( variation == Variation::STAT_DOWN && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.994908;
    if ( variation == Variation::EFF_MC && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.985519;
    if ( variation == Variation::EFF_MC_ERRSYM && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.000984;
    if ( variation == Variation::EFF_DATA && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.983513;
    if ( variation == Variation::SYST_CMSSHAPE && (passingHTTID && probe_Ele_pt>=50 && probe_Ele_pt<100 && probe_Ele_abseta>=2.0 && probe_Ele_abseta<2.5 && passingHTTISO) ) return 0.997643;

    return 1.; // Default
} 

