#include "readableControlFlowGenerator.h"

#include "rules/simpleRules/simpleUnvisitedRule.h"
#include "rules/simpleRules/simpleVisitedOneZoneRule.h"
#include "rules/simpleRules/simpleMergedIfBranchesRule.h"
#include "rules/simpleRules/simpleIfInsideCycleRule.h"

#include "rules/ifRules/ifWithBothUnvisitedRule.h"
#include "rules/ifRules/ifWithOneVisitedRule.h"

#include "rules/loopRules/loopWithBothUnvisitedRule.h"
#include "rules/loopRules/loopWithIterationVisitedRule.h"
#include "rules/loopRules/loopWithNextVisitedRule.h"

#include "rules/switchRules/switchInitializationRule.h"
#include "rules/switchRules/mergedSwitchBranchesRule.h"

using namespace generatorBase;
using namespace qReal;
using namespace semantics;

ReadableControlFlowGenerator::ReadableControlFlowGenerator(
		qrRepo::RepoApi const &repo
		, ErrorReporterInterface &errorReporter
		, GeneratorCustomizer &customizer
		, Id const &diagramId
		, QObject *parent
		, bool isThisDiagramMain)
	: ControlFlowGeneratorBase(repo, errorReporter, customizer, diagramId, parent, isThisDiagramMain)
	, mTravelingForSecondTime(false)
{
}

ControlFlowGeneratorBase *ReadableControlFlowGenerator::cloneFor(Id const &diagramId, bool cloneForNewDiagram)
{
	ReadableControlFlowGenerator * const copy = new ReadableControlFlowGenerator(mRepo
			, mErrorReporter, mCustomizer, diagramId, parent(), false);
	if (!cloneForNewDiagram) {
		delete copy->mValidator;
		copy->mValidator = mValidator;
	}

	return copy;
}

void ReadableControlFlowGenerator::performGeneration()
{
	mAlreadyApplied.clear();
	mTravelingForSecondTime = false;
	mCantBeGeneratedIntoStructuredCode = false;

	for (int iteration = 0; iteration < 2; ++iteration) {
		do {
			mSomethingChangedThisIteration = false;
			ControlFlowGeneratorBase::performGeneration();

			if (mErrorsOccured) {
				mSemanticTree = nullptr;
				return;
			}
		} while (mSomethingChangedThisIteration);

		mTravelingForSecondTime = true;
	}
}

void ReadableControlFlowGenerator::beforeSearch()
{
}

void ReadableControlFlowGenerator::visitRegular(Id const &id
		, QList<LinkInfo> const &links)
{
	ControlFlowGeneratorBase::visitRegular(id, links);
	SimpleUnvisitedRule unvisitedRule(mSemanticTree, id, links[0]);
	SimpleVisitedOneZoneRule visitedOneZoneRule(mSemanticTree, id, links[0]);
	SimpleMergedIfBranchesRule ifMergedBranchesRule(mSemanticTree, id, links[0]);
	MergedSwitchBranchesRule switchMergedBranchesRule(mSemanticTree, id, links[0]);
	SimpleIfInsideCycleRule ifInsideCycle(mSemanticTree, id, links[0]);

	QList<SemanticTransformationRule *> rules;
	if (mTravelingForSecondTime) {
		rules << &visitedOneZoneRule << &ifInsideCycle;
	} else {
		rules << &unvisitedRule << &ifMergedBranchesRule << &switchMergedBranchesRule;
	}

	applyFirstPossible(id, rules, !mTravelingForSecondTime);
}

void ReadableControlFlowGenerator::visitConditional(Id const &id
		, QList<LinkInfo> const &links)
{
	Q_UNUSED(links)

	if (mTravelingForSecondTime) {
		return;
	}

	QPair<LinkInfo, LinkInfo> const branches(ifBranchesFor(id));

	IfWithBothUnvisitedRule bothUnvisitedRule(mSemanticTree, id
			, branches.first, branches.second);
	IfWithOneVisitedRule oneVisitedRule(mSemanticTree, id
			, branches.first, branches.second);

	applyFirstPossible(id, { &oneVisitedRule, &bothUnvisitedRule }, false);
}

void ReadableControlFlowGenerator::visitLoop(Id const &id
		, QList<LinkInfo> const &links)
{
	Q_UNUSED(links)

	if (mTravelingForSecondTime) {
		return;
	}

	QPair<LinkInfo, LinkInfo> const branches(loopBranchesFor(id));

	LoopWithBothUnvisitedRule bothUnvisitedRule(mSemanticTree, id
			, branches.first, branches.second);
	LoopWithIterationVisitedRule iterationVisitedRule(mSemanticTree, id
			, branches.first, branches.second);
	LoopWithNextVisitedRule nextVisitedRule(mSemanticTree, id
			, branches.first, branches.second);

	applyFirstPossible(id, { &bothUnvisitedRule, &iterationVisitedRule, &nextVisitedRule }, false);
}

void ReadableControlFlowGenerator::visitSwitch(Id const &id, QList<LinkInfo> const &links)
{
	SwitchInitializationRule buildingRule(mSemanticTree, id, links, mRepo);
	applyFirstPossible(id, { &buildingRule }, false);
}

void ReadableControlFlowGenerator::afterSearch()
{
}

bool ReadableControlFlowGenerator::cantBeGeneratedIntoStructuredCode() const
{
	return mCantBeGeneratedIntoStructuredCode;
}

bool ReadableControlFlowGenerator::applyFirstPossible(Id const &currentId
		, QList<SemanticTransformationRule *> const &rules
		, bool thereWillBeMoreRules)
{
	if (mAlreadyApplied[currentId]) {
		return true;
	}

	for (SemanticTransformationRule * const rule : rules) {
		if (rule->apply()) {
			mAlreadyApplied[currentId] = true;
			mSomethingChangedThisIteration = true;
			return true;
		}
	}

	if (!thereWillBeMoreRules) {
		mCantBeGeneratedIntoStructuredCode = true;
	}

	return thereWillBeMoreRules;
}
