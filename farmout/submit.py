process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            $inputFileNames
            ),
        inputCommands=cms.untracked.vstring(
            'keep *',
            )
        )

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )

#process.TFileService.fileName=cms.string("$outputFileName")
process.TFileService = cms.Service(
        "TFileService",
        fileName = cms.string("$outputFileName")
        )
