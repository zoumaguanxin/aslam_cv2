#ifndef ASLAM_MATCHER_MATCH_HELPERS_INL_H_
#define ASLAM_MATCHER_MATCH_HELPERS_INL_H_

#include <aslam/common/stl-helpers.h>
#include <aslam/frames/visual-frame.h>
#include <aslam/frames/visual-nframe.h>
#include <glog/logging.h>

namespace aslam {

template<typename MatchWithScore, typename Match>
void convertMatches(
    const typename Aligned<std::vector, MatchWithScore>::type& matches_with_score_A_B,
    typename Aligned<std::vector, Match>::type* matches_A_B) {
  CHECK_NOTNULL(matches_A_B)->clear();
  matches_A_B->reserve(matches_with_score_A_B.size());
  for (const MatchWithScore& match : matches_with_score_A_B) {
    CHECK_GE(match.getIndexApple(), 0) << "The apple index is negative.";
    CHECK_GE(match.getIndexBanana(), 0) << "The banana index is negative.";
    matches_A_B->emplace_back(static_cast<size_t>(match.getIndexApple()),
                              static_cast<size_t>(match.getIndexBanana()));
  }
  CHECK_EQ(matches_with_score_A_B.size(), matches_A_B->size());
}

template<typename MatchWithScore>
void convertMatches(
    const typename Aligned<std::vector, MatchWithScore>::type& matches_with_score_A_B,
    OpenCvMatches* matches_A_B) {
  CHECK_NOTNULL(matches_A_B)->clear();
  matches_A_B->reserve(matches_with_score_A_B.size());
  for (const MatchWithScore& match : matches_with_score_A_B) {
    CHECK_GE(match.getIndexApple(), 0) << "The apple index is negative.";
    CHECK_GE(match.getIndexBanana(), 0) << "The banana index is negative.";
    matches_A_B->emplace_back(match.getIndexApple(), match.getIndexBanana(),
                              static_cast<float>(match.getScore()));
  }
  CHECK_EQ(matches_with_score_A_B.size(), matches_A_B->size());
}

inline void convertMatches(const MatchesWithScore& matches_with_score_A_B, Matches* matches_A_B) {
  convertMatches<MatchWithScore, Match>(matches_with_score_A_B, matches_A_B);
}

template<typename MatchesWithScore>
void convertMatches(const MatchesWithScore& matches_with_score_A_B, Matches* matches_A_B) {
  aslam::MatchesWithScore aslam_matches_with_score_A_B;
  aslam_matches_with_score_A_B.reserve(matches_with_score_A_B.size());
  for (const typename MatchesWithScore::value_type& match : matches_with_score_A_B) {
    aslam_matches_with_score_A_B.emplace_back(match);
  }
  convertMatches(aslam_matches_with_score_A_B, matches_A_B);
}

/// Convert MatchesWithScore to Matches.
template<typename MatchingProblem>
void convertMatches(const typename MatchingProblem::MatchesWithScore& matches_with_score_A_B,
                    typename MatchingProblem::Matches* matches_A_B) {
  convertMatches<typename MatchingProblem::MatchWithScore, typename MatchingProblem::Match>(
      matches_with_score_A_B, matches_A_B);
}
}  // namespace aslam

#endif  // ASLAM_MATCHER_MATCH_HELPERS_INL_H_
