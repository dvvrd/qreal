#pragma once

#include "generatorBase/robotsGeneratorDeclSpec.h"
#include "generatorBase/controlFlowGeneratorBase.h"
#include "generatorBase/semanticTree/semanticTree.h"
#include "rules/semanticTransformationRule.h"

namespace generatorBase {

/// Generates semantic tree in readable style. Code is represented in readable by
/// human style: it consists of if-operators, loop-blocks, switches and so on.
/// If control flow can`t be represented with structured code generation process
/// is considered to be unsuccessfull.
class ROBOTS_GENERATOR_EXPORT ReadableControlFlowGenerator : public ControlFlowGeneratorBase
{
	Q_OBJECT

public:
	ReadableControlFlowGenerator(
			qrRepo::RepoApi const &repo
			, qReal::ErrorReporterInterface &errorReporter
			, GeneratorCustomizer &customizer
			, qReal::Id const &diagramId
			, QObject *parent = 0
			, bool isThisDiagramMain = true);

	/// Implementation of clone operation for readable generator
	ControlFlowGeneratorBase *cloneFor(qReal::Id const &diagramId, bool cloneForNewDiagram) override;

	void beforeSearch() override;

	void visitRegular(qReal::Id const &id, QList<LinkInfo> const &links) override;
	void visitConditional(qReal::Id const &id, QList<LinkInfo> const &links) override;
	void visitLoop(qReal::Id const &id, QList<LinkInfo> const &links) override;
	void visitSwitch(qReal::Id const &id, QList<LinkInfo> const &links) override;

	/// This method can be used for semantic tree debug printing after all
	/// traversal stages.
	void afterSearch() override;

	/// Returns true if some generation errors occured but the generation process may be proceeded with other
	/// control flow generators (non-fatal errors occured).
	bool cantBeGeneratedIntoStructuredCode() const;

private:
	/// Implementation of generation process for readable generator.
	/// Important: the graph in the model would be traversed two or more times
	/// for the emulation of some priority for semantic rules.
	void performGeneration() override;

	bool applyFirstPossible(qReal::Id const &currentId
			, QList<semantics::SemanticTransformationRule *> const &rules
			, bool thereWillBeMoreRules);

	bool mTravelingForSecondTime;
	bool mSomethingChangedThisIteration;
	QMap<qReal::Id, bool> mAlreadyApplied;
	bool mCantBeGeneratedIntoStructuredCode;
};

}
