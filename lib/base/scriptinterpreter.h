/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (http://www.icinga.org/)        *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef SCRIPTINTERPRETER_H
#define SCRIPTINTERPRETER_H

namespace icinga
{

struct ScriptCall
{
	String Method;
	vector<String> Arguments;
	ScriptTask::Ptr Task;
};

/**
 * A script interpreter.
 *
 * @ingroup base
 */
class I2_BASE_API ScriptInterpreter : public Object
{
public:
	typedef shared_ptr<ScriptInterpreter> Ptr;
	typedef weak_ptr<ScriptInterpreter> WeakPtr;

	void EnqueueCall(const ScriptCall& call);

protected:
	ScriptInterpreter(const Script::Ptr& script);

	virtual void ProcessCall(const ScriptCall& call) = 0;

	bool WaitForCall(ScriptCall *call);

	void RegisterMethod(const String& name);

private:
	boost::mutex m_Mutex;
	deque<ScriptCall> m_Calls;
	condition_variable m_CallAvailable;

	boost::thread m_Thread;

	void ThreadWorkerProc(void);
};

}

#endif /* SCRIPTINTERPRETER_H */
