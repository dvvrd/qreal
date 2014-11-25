#pragma once

#include <generatorBase/semanticTree/semanticTree.h>
#include <generatorBase/templateParametrizedEntity.h>

#include "generatorBase/robotsGeneratorDeclSpec.h"

namespace generatorBase {
namespace parts {

/// A storage for all discovered threads in current save.
class ROBOTS_GENERATOR_EXPORT Threads : public TemplateParametrizedEntity
{
public:
	explicit Threads(QString const &pathToTemplates);

	/// Must be called each time when generator gets into the block with the
	/// fork semantics for every block that start new thread.
	/// @param id The initial node of the thread
	void registerThread(qReal::Id const &id);

	/// Must be called each time when semantic tree for some thread was built.
	void threadProcessed(qReal::Id const &id, semantics::SemanticTree &tree);

	/// Returns true if not every registered semantic trees of treads was built.
	bool hasUnprocessedThreads() const;

	/// Returns first unprocessed semantic tree in the threads queue.
	qReal::Id nextUnprocessedThread() const;

	/// Returns a list of semantic trees of threads on all diagrams of the model.
	QList<semantics::SemanticTree *> threads() const;

	/// Returns a list of thread names on all diagrams of the model.
	QStringList threadNames() const;

	/// Generates and returns the code of the section with threads forward declarations.
	QString generateDeclarations() const;

	/// Generates and returns the code of the section with threads code.
	QString generateImplementations() const;

private:
	QString name(semantics::SemanticTree const *tree) const;

	QSet<qReal::Id> mUnprocessedThreads;
	QMap<qReal::Id, semantics::SemanticTree *> mProcessedThreads;
};

}
}
