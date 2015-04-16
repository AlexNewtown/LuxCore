/***************************************************************************
 * Copyright 1998-2015 by authors (see AUTHORS.txt)                        *
 *                                                                         *
 *   This file is part of LuxRender.                                       *
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

#ifndef _SLG_FILESAVER_H
#define	_SLG_FILESAVER_H

#include "slg/slg.h"
#include "slg/renderengine.h"
#include "slg/samplers/sampler.h"
#include "slg/film/film.h"
#include "slg/bsdf/bsdf.h"

namespace slg {

//------------------------------------------------------------------------------
// Scene FileSaver render engine
//------------------------------------------------------------------------------

class FileSaverRenderEngine : public RenderEngine {
public:
	FileSaverRenderEngine(const RenderConfig *cfg, Film *flm, boost::mutex *flmMutex);

	RenderEngineType GetEngineType() const { return FILESAVER; }

	virtual bool IsHorizontalStereoSupported() const {
		return true;
	}

	virtual bool HasDone() const { return true; }
	virtual void WaitForDone() const { }

protected:
	virtual void StartLockLess();
	virtual void StopLockLess() { }

	virtual void BeginSceneEditLockLess() { }
	virtual void EndSceneEditLockLess(const EditActionList &editActions) { SaveScene(); }

	virtual void UpdateFilmLockLess() { }
	virtual void UpdateCounters() { }

private:
	void SaveScene();

	std::string directoryName, renderEngineType;
};

}

#endif	/* _SLG_FILESAVER_H */
