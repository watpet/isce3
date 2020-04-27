##CEOS Dataset Summary Record - Common section
def DatasetSummaryRecordCommonType():
    '''
    Data Set Summary Record.
    http://www.ga.gov.au/__data/assets/pdf_file/0019/11719/GA10287.pdf Pg: 3-26.
    '''
    from .BasicTypes import (BlankType, StringType, IntegerType, FloatType, BinaryType, MultiType)  
    from .CEOSHeaderType import CEOSHeaderType
    return MultiType( CEOSHeaderType().mapping + 
                      [('DSRecordSequenceNumber', IntegerType(4)),
                       ('SARChannelIndicator', StringType(4)),
                       ('SceneIdentifier', StringType(32)),
                       ('SceneDesignator', StringType(16)),
                       ('InputSceneCenterTime', StringType(32)),
                       ('blanks1', BlankType(16)),
                       ('SceneCenterLatitude', BlankType(16)),
                       ('SceneCenterLongitude', BlankType(16)),
                       ('SceneCenterHeading', BlankType(16)),
                       ('EllipsoidDesignator', StringType(16)),
                       ('EllipsoidSemiMajorAxisInKm', FloatType(16)),
                       ('EllipsoidSemiMinorAxisInKm', FloatType(16)),
                       ('EarthMassIn1024Kg', FloatType(16)),
                       ('GravitationalConstant', FloatType(16)),
                       ('EllipsoidJ2Parameter', FloatType(16)),
                       ('EllipsoidJ3Parameter', FloatType(16)),
                       ('EllipsoidJ4Parameter', FloatType(16)),
                       ('blanks2', BlankType(16)),
                       ('AverageTerrainHeight', FloatType(16)),
                       ('SceneCenterLineNumber', IntegerType(8)),
                       ('SceneCenterPixelNumber', IntegerType(8)),
                       ('ProcessedSceneLengthInKm', FloatType(16)),
                       ('ProcessedSceneWidthInKm', FloatType(16)),
                       ('blanks3', BlankType(16)),
                       ('NumberOfSARChannels', IntegerType(4)),
                       ('blanks4', BlankType(4)),
                       ('SensorPlatformMissionIdentifier', StringType(16)),
                       ('SensorIDAndMode', StringType(32)),
                       ('OrbitNumber', IntegerType(8)),
                       ('SensorPlatformLatitude', BlankType(8)),
                       ('SensorPlatformLongitude', BlankType(8)),
                       ('SensorPlatformHeading', BlankType(8)),
                       ('SensorClockAngle', FloatType(8)),
                       ('SceneCenterIncidenceAngle', FloatType(8)),
                       ('blanks5', BlankType(8)),
                       ('RadarWavelengthInm', FloatType(16)),
                       ('MotionCompensationIndicator', StringType(2)),
                       ('RangePulseCodeSpecifier', StringType(16)),
                       ('RangePulseAmplitudeCoefficientDCTerm', FloatType(16)),
                       ('RangePulseAmplitudeCoefficientLinearTerm', FloatType(16)),
                       ('RangePulseAmplitudeCoefficientQuadraticTerm', FloatType(16)),
                       ('RangePulseAmplitudeCoefficientCubicTerm', FloatType(16)),
                       ('RangePulseAmplitudeCoefficientQuarticTerm', FloatType(16)),
                       ('RangePulsePhaseCoefficientDCTerm', FloatType(16)),
                       ('RangePulsePhaseCoefficientLinearTerm', FloatType(16)),
                       ('RangePulsePhaseCoefficientQuadraticTerm', FloatType(16)),
                       ('RangePulsePhaseCoefficientCubicTerm', FloatType(16)),
                       ('RangePulsePhaseCoefficientQuarticTerm', FloatType(16)),
                       ('DownlinkedDataChirpExtractionIndex', BlankType(8)),
                       ('blanks6', BlankType(8)),
                       ('SamplingRateInMHz', FloatType(16)),
                       ('RangeGateAtEarlyEdgeAtStartOfImageInusec', FloatType(16)),
                       ('RangePulseLengthInusec', FloatType(16)),
                       ('BasebandConversionFlag', StringType(4)),
                       ('RangeCompressedFlag', StringType(4)),
                       ('ReceiverGainCopolEarlyEdgeindB', FloatType(16)),
                       ('ReceiverGainXpolEarlyEdgeindB', FloatType(16)),
                       ('QuantizationBitsPerChannel', IntegerType(8)),
                       ('QuantizationDescriptor', StringType(12)),
                       ('DCBiasIComponent', FloatType(16)),
                       ('DCBiasQComponent', FloatType(16)),
                       ('GainImbalanceforIQ', FloatType(16)),
                       ('blanks7', BlankType(16)),
                       ('blanks8', BlankType(16)),
                       ('AntennaElectronicBoresightInDeg', FloatType(16)),
                       ('AntennaMechanicalBoresightInDeg', FloatType(16)),
                       ('EchoTrackerOnOffFlag', StringType(4)),
                       ('NominalPRFInmHz', FloatType(16)),
                       ('EffectiveTwoWayAntennaElevation3dBBeamwidthInDeg', FloatType(16)),
                       ('EffectiveTwoWayAntennaAzimuth3dBBeamwidthInDeg', FloatType(16)),
                       ('SatelliteEncodedBinaryTimeCode', IntegerType(16)),
                       ('SatelliteClockTime', StringType(32)),
                       ('SatelliteClockIncrementInnsec', IntegerType(16)),
                       ('ProcessingFacilityIdentifier', StringType(16)),
                       ('ProcessingSystemIdentifier', StringType(8)),
                       ('ProcessingVersionIdentifier', StringType(8)),
                       ('ProcessingFacilityProcessCode', StringType(16)),
                       ('ProductLevelCode', StringType(16)),
                       ('ProductTypeSpecifier', StringType(32)),
                       ('ProcessingAlgorithmIdentifier', StringType(32)),
                       ('NominalEffectiveAzimuthLooks', FloatType(16)),
                       ('NominalEffectiveRangeLooks', FloatType(16)),
                       ('BandwidthPerLookInAzimuthHz', FloatType(16)),
                       ('BandwidthPerLookInRangeHz', FloatType(16)),
                       ('TotalProcessorBandwidthInAzimuth', FloatType(16)),
                       ('TotalProcessorBandwidthInRange', FloatType(16)),
                       ('WeightingFunctionInAzimuth', StringType(32)),
                       ('WeightingFunctionInRange', StringType(32)),
                       ('DataInputSource', StringType(16)),
                       ('Nominal3dBResolutionInGroundRangeInm', FloatType(16)),
                       ('Nominal3dBResolutionInAzimuthInm', FloatType(16)),
                       ('ConstantRadiometricParameterBias', FloatType(16)),
                       ('LinearRadiometricParameterGain', FloatType(16)),
                       ('AlongTrackDopplerConstantTermInHz', FloatType(16)),
                       ('AlongTrackDopplerLinearTermInHzPerPixel', FloatType(16)),
                       ('AlongTrackDopplerQuadraticTermInHzPerPixel2', FloatType(16)),
                       ('blanks9', BlankType(16)),
                       ('CrossTrackDopplerConstantTermInHz', FloatType(16)),
                       ('CrossTrackDopplerLinearTermInHzPerPixel', FloatType(16)),
                       ('CrossTrackDopplerLinearTermInHzPerPixel2', FloatType(16)),
                       ('TimeDirectionIndicatorAlongPixel', StringType(8)),
                       ('TimeDirectionIndicatorAlongLine', StringType(8)),
                       ('AlongTrackDopplerRateConstantTermInHzPerSec', FloatType(16)),
                       ('AlongTrackDopplerRateLinearTermInHzPerSecPerPixel', FloatType(16)),
                       ('AlongTrackDopplerRateQuadraticTermInHzPerSecPerPixel2', FloatType(16)),
                       ('blanks10', BlankType(16)),
                       ('CrossTrackDopplerRateConstantTermInHzPerSec', FloatType(16)),
                       ('CrossTrackDopplerRateLinearTermInHzPerSecPerPixel', FloatType(16)),
                       ('CrossTrackDopplerRateQuadraticTermInHzPerSecPerPixel2', FloatType(16)),
                       ('blanks11', BlankType(16)),
                       ('LineContentIndicator', StringType(8)),
                       ('ClutterLockAppliedFlag', StringType(4)),
                       ('AutoFocusingAppliedFlag', StringType(4)),
                       ('LineSpacingInm', FloatType(16)),
                       ('PixelSpacingInm', FloatType(16)),
                       ('ProcessorRangeCompressionDesignator', StringType(16)),
                       ('blanks12', BlankType(16)),
                       ('blanks13', BlankType(16))])
