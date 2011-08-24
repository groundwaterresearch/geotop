
/* STATEMENT:
 
 GEOtop MODELS THE ENERGY AND WATER FLUXES AT THE LAND SURFACE
 GEOtop 1.145 'Montebello' - 8 Nov 2010
 
 Copyright (c), 2010 - Stefano Endrizzi - Geographical Institute, University of Zurich, Switzerland - stefano.endrizzi@geo.uzh.ch 
 
 This file is part of GEOtop 1.145 'Montebello'
 
 GEOtop 1.145 'Montebello' is a free software and is distributed under GNU General Public License v. 3.0 <http://www.gnu.org/licenses/>
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE
 
 GEOtop 1.145 'Montebello' is distributed as a free software in the hope to create and support a community of developers and users that constructively interact.
 If you just use the code, please give feedback to the authors and the community.
 Any way you use the model, may be the most trivial one, is significantly helpful for the future development of the GEOtop model. Any feedback will be highly appreciated.
 
 If you have satisfactorily used the code, please acknowledge the authors.
 
 */

char *keywords_num[num_par_number] = {"TimeStepEnergyAndWater", "InitDateDDMMYYYYhhmm", 
	"EndDateDDMMYYYYhhmm", "NumSimulationTimes", 
	"StandardTimeSimulation", "DtPlotDischarge", "DtPlotPoint", 
	"DtPlotBasin", "NumLowPassFilterOnDemForAll", "NumLowPassFilterOnDemForCurv", 
	"FlagSkyViewFactor", "FormatOutputMaps", "PointSim", "RecoverSim", "NumLandCoverTypes", 
	"SoilRoughness", "ThresSnowSoilRough", "VegHeight", "ThresSnowVegUp", "ThresSnowVegDown", 
	"LSAI", "CanopyFraction", "DecayCoeffCanopy", "VegSnowBurying", "RootDepth", 
	"MinStomatalRes", "VegReflectVis", "VegReflNIR", "VegTransVis", "VegTransNIR", 
	"LeafAngles", "CanDensSurface", "SoilAlbVisDry", "SoilAlbNIRDry", "SoilAlbVisWet", 
	"SoilAlbNIRWet", "SoilEmissiv", "SurFlowResLand", "RoughElemXUnitArea",
	"RoughElemDiam", "FrozenSoilHydrCondReduction", "RichardTol", "RichardMaxIter","RichardInitForc", 
	"MinLambdaWater","MaxTimesMinLambdaWater","ExitMinLambdaWater","MaxTimesHalvingTimeStepWater",
	"SurFlowResExp", "ThresWaterDepthLandDown", "ThresWaterDepthLandUp", 
	"SurFlowResChannel", "ThresWaterDepthChannelUp",  
	"RatioChannelWidthPixelWidth", "ChannelDepression",
	"MaxCourantSupFlowLand","MaxCourantSupFlowChannel","MinSupWaterDepthLand","MinSupWaterDepthChannel","MinTimeStepSupFlow",
	"Latitude", "Longitude", "Vmin" , "RHmin" , "AlphaSnow", "HighestNodeCorrespondsToLayer","HeatEqTol", "HeatEqMaxIter",
	"MinLambdaEnergy","MaxTimesMinLambdaEnergy","ExitMinLambdaEnergy","MaxTimesHalvingTimeStepEnergy",
	"CanopyMaxIter", "BusingerMaxIter", "TsMaxIter" , "LocMaxIter" , "CanopyStabCorrection" , 
	"Iobsint" , "Dn" , "SlopeWeight" , "CurvatureWeight" , "ZeroTempAmplitDepth",
	"ZeroTempAmplitTemp", "BottomBoundaryHeatFlux","InitSWE" , "InitSnowDensity" , "InitSnowTemp" , 
	"InitSnowAge" ,"ThresTempRain" , "ThresTempSnow" , "DewTempOrNormTemp" , "AlbExtParSnow" , 
	"FreshSnowReflVis" ,"FreshSnowReflNIR" , "IrriducibleWatSatSnow" , "SnowEmissiv" , 
	"SnowRoughness" , "SnowCorrFactor" ,"RainCorrFactor" , 
	"NumMaxSnowLayers" , "InfiniteSnowLayer" , "MaxSnowPorosity" , 
	"DrySnowDefRate","SnowDensityCutoff","WetSnowDefRate","SnowViscosity",
	"FetchUp","FetchDown","BlowingSnowSoftLayerIceContent", "TimeStepBlowingSnow",
	"SnowSMIN","SnowSMAX","SnowCURV","MinLayerThicknessSnow","MaxLayerThicknessSnow",
	"InitGlacierDepth","InitGlacierDensity","InitGlacierTemp","IrriducibleWatSatGlacier",
	"NumMaxGlacierLayers","MinLayerThicknessGlacier","MaxLayerThicknessGlacier",
	"LWinParameterization","MoninObukhov","WaterBalance","EnergyBalance",
	"BlowingSnow","PixelCoordinates",
	"PointID","CoordinatePointX","CoordinatePointY","PointElevation",
	"PointLandCoverType","PointSoilType","PointSlope","PointAspect","PointSkyViewFactor",
	"PointCurvatureNorthSouthDirection","PointCurvatureWestEastDirection",
	"PointCurvatureNorthwestSoutheastDirection","PointCurvatureNortheastSouthwestDirection",
	"PointDrainageLateralDistance","PointDepthFreeSurface",
	"PointHorizon","PointMaxSWE","PointLatitude","PointLongitude",
	"SavingPoints","OutputSoilMaps","OutputSnowMaps","OutputGlacierMaps",
	"OutputSurfEBALMaps","OutputVegetationMaps","OutputMeteoMaps","SpecialPlotBegin",
	"SpecialPlotEnd","SoilLayerTypes","InitWaterTableHeightOverTopoSurface",
	"DefaultSoilTypeLand","DefaultSoilTypeChannel",
	"SoilLayerThicknesses","SoilLayerNumber",
	"InitSoilPressure","InitSoilTemp","NormalHydrConductivity","LateralHydrConductivity",
	"ThetaRes","WiltingPoint","FieldCapacity","ThetaSat","AlphaVanGenuchten","NVanGenuchten",
	"VMualem","ThermalConductivitySoilSolids","ThermalCapacitySoilSolids",
	"SpecificStorativity","InitSoilPressureBedrock","InitSoilTempBedrock","NormalHydrConductivityBedrock",
	"LateralHydrConductivityBedrock","ThetaResBedrock","WiltingPointBedrock",
	"FieldCapacityBedrock","ThetaSatBedrock","AlphaVanGenuchtenBedrock",
	"NVanGenuchtenBedrock","VMualemBedrock","ThermalConductivitySoilSolidsBedrock",
	"ThermalCapacitySoilSolidsBedrock","SpecificStorativityBedrock",	
	"MeteoStationsID","NumberOfMeteoStations","MeteoStationCoordinateX","MeteoStationCoordinateY",
	"MeteoStationLatitude","MeteoStationLongitude","MeteoStationElevation",
	"MeteoStationSkyViewFactor","MeteoStationStandardTime",
	"MeteoStationWindVelocitySensorHeight","MeteoStationTemperatureSensorHeight",
	"LapseRateTemp","LapseRateDewTemp","LapseRatePrec","MinPrecIncreaseFactorWithElev","MaxPrecDecreaseFactorWithElev",
	"DatePoint","JulianDayFromYear0Point","TimeFromStartPoint","PeriodPoint","RunPoint",
	"IDPointPoint","PsnowPoint","PrainPoint","PsnowNetPoint","PrainNetPoint","PrainOnSnowPoint",
	"WindSpeedPoint","WindDirPoint","RHPoint","AirPressPoint","AirTempPoint","TDewPoint",
	"TsurfPoint","TvegPoint","TCanopyAirPoint","SurfaceEBPoint","SoilHeatFluxPoint",
	"SWinPoint","SWbeamPoint","SWdiffPoint","LWinPoint","LWinMinPoint","LWinMaxPoint",
	"SWNetPoint","LWNetPoint","HPoint","LEPoint","CanopyFractionPoint","LSAIPoint",
	"z0vegPoint","d0vegPoint","EstoredCanopyPoint","SWvPoint",
	"LWvPoint","HvPoint","LEvPoint","HgUnvegPoint","LEgUnvegPoint","HgVegPoint","LEgVegPoint",
	"EvapSurfacePoint","TraspCanopyPoint","WaterOnCanopyPoint","SnowOnCanopyPoint","QVegPoint",
	"QSurfPoint","QAirPoint","QCanopyAirPoint","LObukhovPoint","LObukhovCanopyPoint",
	"WindSpeedTopCanopyPoint","DecayKCanopyPoint","SWupPoint","LWupPoint","HupPoint",
	"LEupPoint","SnowDepthPoint","SWEPoint","SnowDensityPoint","SnowTempPoint",
	"SnowMeltedPoint","SnowSublPoint","SWEBlownPoint","SWESublBlownPoint",
	"GlacDepthPoint","GWEPoint","GlacDensityPoint","GlacTempPoint","GlacMeltedPoint",
	"GlacSublPoint","ThawedSoilDepthPoint","WaterTableDepthPoint","DefaultPoint",
	"DateBasin","JulianDayFromYear0Basin","TimeFromStartBasin","PeriodBasin","RunBasin",
	"PRainNetBasin","PSnowNetBasin","PRainBasin","PSnowBasin","AirTempBasin","TSurfBasin",
	"TvegBasin","EvapSurfaceBasin","TraspCanopyBasin","LEBasin","HBasin","SWNetBasin",
	"LWNetBasin","LEvBasin","HvBasin","SWvBasin","LWvBasin","SWinBasin","LWinBasin",
	"MassErrorBasin","DefaultBasin","DateSnow","JulianDayFromYear0Snow","TimeFromStartSnow",
	"PeriodSnow","RunSnow","IDPointSnow","WaterEquivalentSnow","DepthSnow","DensitySnow",
	"TempSnow","IceContentSnow","WatContentSnow","DefaultSnow","DateGlac","JulianDayFromYear0Glac",
	"TimeFromStartGlac","PeriodGlac","RunGlac","IDPointGlac","WaterEquivalentGlac","DepthGlac",
	"DensityGlac","TempGlac","IceContentGlac","WatContentGlac","DefaultGlac","DateSoil",
	"JulianDayFromYear0Soil","TimeFromStartSoil","PeriodSoil","RunSoil","IDPointSoil","DefaultSoil"};

char *keywords_char[num_par_char] = {"HeaderDateDDMMYYYYhhmmMeteo","HeaderJulianDayfrom0Meteo",
	"HeaderIPrec","HeaderWindVelocity", "HeaderWindDirection", 
	"HeaderWindX", "HeaderWindY", "HeaderRH", "HeaderAirTemp", "HeaderDewTemp", "HeaderAirPress", 
	"HeaderSWglobal", "HeaderSWdirect", "HeaderSWdiffuse", "HeaderCloudSWTransmissivity", 
	"HeaderCloudFactor", "HeaderLWin", "HeaderSWnet", "HeaderSoilDz", "HeaderSoilInitPres",
	"HeaderSoilInitTemp", "HeaderNormalHydrConductivity", "HeaderLateralHydrConductivity", 
	"HeaderThetaRes", "HeaderWiltingPoint", 
	"HeaderFieldCapacity", "HeaderThetaSat", "HeaderAlpha", "HeaderN", "HeaderV",
	"HeaderKthSoilSolids", "HeaderCthSoilSolids", "HeaderSpecificStorativity",
	"HeaderHorizonAngle", "HeaderHorizonHeight" ,"TimeStepsFile", "SoilParFile", 
	"MeteoFile", "MeteoStationsListFile","LapseRateFile", "HorizonMeteoStationFile","PointFile",
	"HorizonPoint", "TimeDependentVegetationParameterFile", 
	"DemFile", "LandCoverMapFile", "SoilMapFile", "SkyViewFactorMapFile", 
	"SlopeMapFile", "RiverNetwork", "AspectMapFile", "CurvaturesMapFile", 
	"BedrockDepthMapFile", "InitSnowDepthMapFile", "InitSnowAgeMapFile", 
	"InitGlacierDepthMapFile","DischargeFile", "BasinOutputFile","BasinOutputFileWriteEnd",
	"PointOutputFile","PointOutputFileWriteEnd", "SoilTempProfileFile","SoilTempProfileFileWriteEnd",
	"SoilAveragedTempProfileFile", "SoilAveragedTempProfileFileWriteEnd", 
	"SoilLiqWaterPressProfileFile", "SoilLiqWaterPressProfileFileWriteEnd",
	"SoilTotWaterPressProfileFile", "SoilTotWaterPressProfileFileWriteEnd",
	"SoilLiqContentProfileFile", "SoilLiqContentProfileFileWriteEnd",
	"SoilAveragedLiqContentProfileFile", "SoilAveragedLiqContentProfileFileWriteEnd",
	"SoilIceContentProfileFile", "SoilIceContentProfileFileWriteEnd",
	"SoilAveragedIceContentProfileFile", "SoilAveragedIceContentProfileFileWriteEnd",
	"SnowProfileFile","SnowProfileFileWriteEnd", "GlacierProfileFile","GlacierProfileFileWriteEnd",
	"SnowCoveredAreaFile", "SoilTempTensorFile", "FirstSoilLayerTempMapFile", 
	"SoilAveragedTempTensorFile", "FirstSoilLayerAveragedTempMapFile", "SoilLiqContentTensorFile", 
	"FirstSoilLayerLiqContentMapFile", "IceLiqContentTensorFile", 
	"FirstSoilLayerIceContentMapFile", "LandSurfaceWaterDepthMapFile", 
	"RadiationMapFile", "SurfaceHeatFluxMapFile", "SurfaceSensibleHeatFluxMapFile", 
	"SurfaceLatentHeatFluxMapFile", "SurfaceTempMapFile", "PrecipitationMapFile", 
	"CanopyInterceptedWaterMapFile", "SoilLiqWaterPressTensorFile", 
	"SnowDepthMapFile", "GlacierDepthMapFile", "SnowMeltedMapFile", "SnowSublMapFile", 
	"GlacierMeltedMapFile", "GlacierSublimatedMapFile", 
	"AirTempMapFile", "WindSpeedMapFile", "WindDirMapFile", "RelHumMapFile", "SWEMapFile", 
	"GlacierWaterEqMapFile", "SnowDurationMapFile", "AveragedSnowDepthMapFile", 
	"ThawedDepthMapFile", "WaterTableDepthMapFile", "FrostTableDepthMapFile", 
	"SpecificPlotSurfaceHeatFluxMapFile", "SpecificPlotTotalSensibleHeatFluxMapFile", 
	"SpecificPlotTotalLatentHeatFluxMapFile", "SpecificPlotSurfaceSensibleHeatFluxMapFile", 
	"SpecificPlotSurfaceLatentHeatFluxMapFile", "SpecificPlotVegSensibleHeatFluxMapFile", 
	"SpecificPlotVegLatentHeatFluxMapFile", "SpecificPlotIncomingShortwaveRadMapFile", 
	"SpecificPlotNetSurfaceShortwaveRadMapFile", "SpecificPlotNetVegShortwaveRadMapFile", 
	"SpecificPlotIncomingLongwaveRadMapFile", "SpecificPlotNetSurfaceLongwaveRadMapFile", 
	"SpecificPlotNetVegLongwaveRadMapFile", "SpecificPlotCanopyAirTempMapFile", 
	"SpecificPlotSurfaceTempMapFile", "SpecificPlotVegTempMapFile", 
	"SpecificPlotAboveVegAirTempMapFile", "SpecificPlotWindSpeedMapFile", 
	"SpecificPlotWindDirMapFile", "SpecificPlotRelHumMapFile", "SpecificPlotSnowDepthMapFile", 
	"SpecificPlotSurfaceWaterContentMapFile", "RecoverSoilWatPres", "RecoverSoilIceCont", 
	"RecoverSoilTemp", "RecoverSnowLayerThick", "RecoverSnowLiqMass", "RecoverSnowIceMass", 
	"RecoverSnowTemp", "RecoverGlacierLayerThick", "RecoverGlacierLiqMass", 
	"RecoverGlacierIceMass", "RecoverGlacierTemp", "RecoverSnowLayerNumber", 
	"RecoverGlacierLayerNumber", "RecoverNonDimensionalSnowAge", "RecoverDimensionalSnowAge", 
	"RecoverLandSurfaceWaterDepth", "RecoverLiqWaterOnCanopy", "RecoverSnowOnCanopy", 
	"RecoverVegTemp", "RecoverSoilWatPresChannel","RecoverSoilIceContChannel","RecoverSoilTempChannel",
	"HeaderDatePoint","HeaderJulianDayFromYear0Point","HeaderTimeFromStartPoint",
	"HeaderPeriodPoint","HeaderRunPoint","HeaderIDPointPoint",
	"HeaderPsnowPoint","HeaderPrainPoint","HeaderPsnowNetPoint",
	"HeaderPrainNetPoint","HeaderPrainOnSnowPoint","HeaderWindSpeedPoint",
	"HeaderWindDirPoint","HeaderRHPoint","HeaderAirPressPoint","HeaderAirTempPoint",
	"HeaderTDewPoint","HeaderTsurfPoint","HeaderTvegPoint","HeaderTCanopyAirPoint",
	"HeaderSurfaceEBPoint","HeaderSoilHeatFluxPoint","HeaderSWinPoint","HeaderSWbeamPoint",
	"HeaderSWdiffPoint","HeaderLWinPoint","HeaderLWinMinPoint","HeaderLWinMaxPoint",
	"HeaderSWNetPoint","HeaderLWNetPoint","HeaderHPoint","HeaderLEPoint",
	"HeaderCanopyFractionPoint","HeaderLSAIPoint","Headerz0vegPoint","Headerd0vegPoint",
	"HeaderEstoredCanopyPoint","HeaderSWvPoint","HeaderLWvPoint","HeaderHvPoint",
	"HeaderLEvPoint","HeaderHgUnvegPoint","HeaderLEgUnvegPoint","HeaderHgVegPoint",
	"HeaderLEgVegPoint","HeaderEvapSurfacePoint","HeaderTraspCanopyPoint",
	"HeaderWaterOnCanopyPoint","HeaderSnowOnCanopyPoint","HeaderQVegPoint",
	"HeaderQSurfPoint","HeaderQAirPoint","HeaderQCanopyAirPoint","HeaderLObukhovPoint",
	"HeaderLObukhovCanopyPoint","HeaderWindSpeedTopCanopyPoint","HeaderDecayKCanopyPoint",
	"HeaderSWupPoint","HeaderLWupPoint","HeaderHupPoint","HeaderLEupPoint",
	"HeaderSnowDepthPoint","HeaderSWEPoint","HeaderSnowDensityPoint","HeaderSnowTempPoint",
	"HeaderSnowMeltedPoint","HeaderSnowSublPoint","HeaderSWEBlownPoint",
	"HeaderSWESublBlownPoint","HeaderGlacDepthPoint","HeaderGWEPoint","HeaderGlacDensityPoint",
	"HeaderGlacTempPoint","HeaderGlacMeltedPoint","HeaderGlacSublPoint",
	"HeaderThawedSoilDepthPoint","HeaderWaterTableDepthPoint",
	"HeaderDateBasin","HeaderJulianDayFromYear0Basin",
	"HeaderTimeFromStartBasin","HeaderPeriodBasin","HeaderRunBasin",
	"HeaderPRainNetBasin","HeaderPSnowNetBasin","HeaderPRainBasin",
	"HeaderPSnowBasin","HeaderAirTempBasin","HeaderTSurfBasin","HeaderTvegBasin",
	"HeaderEvapSurfaceBasin","HeaderTraspCanopyBasin","HeaderLEBasin","HeaderHBasin",
	"HeaderSWNetBasin","HeaderLWNetBasin","HeaderLEvBasin","HeaderHvBasin","HeaderSWvBasin",
	"HeaderLWvBasin","HeaderSWinBasin","HeaderLWinBasin","HeaderMassErrorBasin",
	"HeaderDateSnow","HeaderJulianDayFromYear0Snow",
	"HeaderTimeFromStartSnow","HeaderPeriodSnow","HeaderRunSnow",
	"HeaderIDPointSnow","HeaderWaterEquivalentSnow","HeaderDepthSnow",
	"HeaderDensitySnow","HeaderTempSnow","HeaderIceContentSnow","HeaderWatContentSnow",
	"HeaderDateGlac","HeaderJulianDayFromYear0Glac",
	"HeaderTimeFromStartGlac","HeaderPeriodGlac","HeaderRunGlac","HeaderIDPointGlac",
	"HeaderWaterEquivalentGlac","HeaderDepthGlac",
	"HeaderDensityGlac","HeaderTempGlac","HeaderIceContentGlac","HeaderWatContentGlac",
	"HeaderDateSoil","HeaderJulianDayFromYear0Soil",
	"HeaderTimeFromStartSoil","HeaderPeriodSoil","HeaderRunSoil","HeaderIDPointSoil",
	"HeaderPointID","HeaderCoordinatePointX","HeaderCoordinatePointY",
	"HeaderPointElevation","HeaderPointLandCoverType","HeaderPointSoilType","HeaderPointSlope",
	"HeaderPointAspect","HeaderPointSkyViewFactor","HeaderPointCurvatureNorthSouthDirection",
	"HeaderPointCurvatureWestEastDirection","HeaderPointCurvatureNorthwestSoutheastDirection",
	"HeaderPointCurvatureNortheastSouthwestDirection","HeaderPointDrainageLateralDistance","HeaderPointDepthFreeSurface",
	"HeaderPointHorizon","HeaderPointMaxSWE","HeaderPointLatitude","HeaderPointLongitude",
	"HeaderDateDDMMYYYYhhmmLapseRates","HeaderLapseRateTemp",
	"HeaderLapseRateDewTemp","HeaderLapseRatePrec",
	"HeaderIDMeteoStation","HeaderMeteoStationCoordinateX","HeaderMeteoStationCoordinateY",
	"HeaderMeteoStationLatitude","HeaderMeteoStationLongitude","HeaderMeteoStationElevation",
	"HeaderMeteoStationSkyViewFactor","HeaderMeteoStationStandardTime"};

