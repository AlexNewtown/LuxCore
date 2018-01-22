/***************************************************************************
 * Copyright 1998-2018 by authors (see AUTHORS.txt)                        *
 *                                                                         *
 *   This file is part of LuxCoreRender.                                   *
 *                                                                         *
 * Licensed under the Apache License, Version 2.0 (the "License");         *
 * you may not use this file except in compliance with the License.        *
 * You may obtain a copy of the License at                                 *
 *                                                                         *
 *     http://www.apache.org/licenses/LICENSE-2.0                          *
 *                                                                         *
 * Unless required by applicable law or agreed to in writing, software     *
 * distributed under the License is distributed on an "AS IS" BASIS,       *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
 * See the License for the specific language governing permissions and     *
 * limitations under the License.                                          *
 ***************************************************************************/

#ifndef _SLG_SOBOL_SAMPLER_H
#define	_SLG_SOBOL_SAMPLER_H

#include <string>
#include <vector>

#include "luxrays/core/randomgen.h"
#include "luxrays/utils/atomic.h"

#include "slg/slg.h"
#include "slg/film/film.h"
#include "slg/samplers/sampler.h"

namespace slg {

//------------------------------------------------------------------------------
// SobolSamplerSharedData
//
// Used to share sampler specific data across multiple threads
//------------------------------------------------------------------------------

class SobolSamplerSharedData : public SamplerSharedData {
public:
	SobolSamplerSharedData(luxrays::RandomGenerator *rndGen, Film *film);
	virtual ~SobolSamplerSharedData() { }

	static SamplerSharedData *FromProperties(const luxrays::Properties &cfg,
			luxrays::RandomGenerator *rndGen, Film *film);

	void GetNewPixelIndex(u_int &index, u_int &sobolPass, u_int &seed);

	u_int seedBase;
	u_int filmRegionPixelCount;

private:
	luxrays::SpinLock spinLock;
	u_int pixelIndex, pass;
};

//------------------------------------------------------------------------------
// Sobol sampler
//
// This sampler is based on Blender Cycles Sobol implementation.
//------------------------------------------------------------------------------

#define SOBOL_STARTOFFSET 32
#define SOBOL_THREAD_WORK_SIZE 4096

extern void SobolGenerateDirectionVectors(u_int *vectors, const u_int dimensions);

class SobolSampler : public Sampler {
public:
	SobolSampler(luxrays::RandomGenerator *rnd, Film *flm,
			const FilmSampleSplatter *flmSplatter,
			SobolSamplerSharedData *samplerSharedData);
	virtual ~SobolSampler();

	virtual SamplerType GetType() const { return GetObjectType(); }
	virtual std::string GetTag() const { return GetObjectTag(); }
	virtual void RequestSamples(const u_int size);

	virtual float GetSample(const u_int index);
	virtual void NextSample(const std::vector<SampleResult> &sampleResults);

	//--------------------------------------------------------------------------
	// Static methods used by SamplerRegistry
	//--------------------------------------------------------------------------

	static SamplerType GetObjectType() { return SOBOL; }
	static std::string GetObjectTag() { return "SOBOL"; }
	static luxrays::Properties ToProperties(const luxrays::Properties &cfg);
	static Sampler *FromProperties(const luxrays::Properties &cfg, luxrays::RandomGenerator *rndGen,
		Film *film, const FilmSampleSplatter *flmSplatter, SamplerSharedData *sharedData);
	static slg::ocl::Sampler *FromPropertiesOCL(const luxrays::Properties &cfg);

private:
	void InitNewSample();
	float GetSobolSample(const u_int index);

	static const luxrays::Properties &GetDefaultProps();

	u_int SobolDimension(const u_int index, const u_int dimension) const;

	SobolSamplerSharedData *sharedData;
	u_int *directions;

	u_int pixelIndexBase, pixelIndexOffset, pass;
	luxrays::TauswortheRandomGenerator rngGenerator;

	float rng0, rng1;
	float sample0, sample1;
};

}

#endif	/* _SLG_SOBOL_SAMPLER_H */
