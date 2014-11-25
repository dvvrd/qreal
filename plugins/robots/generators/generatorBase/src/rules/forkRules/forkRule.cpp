#include "forkRule.h"

#include "generatorBase/parts/threads.h"

using namespace generatorBase::semantics;
using namespace qReal;

ForkRule::ForkRule(SemanticTree *tree, Id const &id, QList<LinkInfo> const &threads, parts::Threads &threadsStorage)
	: SemanticTransformationRule(tree, id)
	, mThreads(threads)
	, mThreadsStorage(threadsStorage)
{
}

bool ForkRule::apply()
{
	ForkNode * const fork = static_cast<ForkNode *>(mTree->findNodeFor(mId));
	for (LinkInfo const &thread : mThreads) {
		mThreadsStorage.registerThread(thread.target);
		fork->appendThread(thread.target);
	}

	return true;
}
