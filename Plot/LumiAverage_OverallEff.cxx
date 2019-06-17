#include "ProduceLumiAveragedGraphs_2016Data.cxx"

Double_t LumiAverage(Double_t value_before, Double_t value_after)
{
  Double_t lumi_tot = LUMI_BEFOREFIX + LUMI_AFTERFIX;
  Double_t frac_before = LUMI_BEFOREFIX / lumi_tot;
  Double_t frac_after  = LUMI_AFTERFIX / lumi_tot;

  return value_before*frac_before + value_after*frac_after;

}
void LumiAverage_OverallEff()
{
  // -- Mu50
  // Double_t eff_beforeFix = 0.8954;
  // Double_t eff_afterFix = 0.9133;

  // -- IsoMu24
  Double_t eff_beforeFix = 0.89844;
  Double_t eff_afterFix = 0.90043;

  cout << "eff_beforeFix = " << eff_beforeFix << ", eff_afterFix = " << eff_afterFix << endl;
  cout << "Lumi-averaged overall efficiency = " << LumiAverage(eff_beforeFix, eff_afterFix) << endl;
}

