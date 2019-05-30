# contributing to coloring-graphs

this repository uses git branches to manage development, testing,
and deployment workflow. to contribute, please make sure you are
committing and pushing on the correct branch

## workflow

workflow is split between
- master
- dev
- feature branches (ad-hoc)

### master

- **committing**

  please do not work on this branch or make changes unless absolutely
  necessary

  only compiling/working code goes here:
  the code must not only compile, but also be sensible working code 
  rather than have some broken feature or massive bugs
  
- **merging**

  once you have compiling **and** working code in some branch, you can
  merge it into master. carefully review any merge conflicts that may
  go unnoticed. an easy way to do this is to
  `git diff --name-only --diff-filter=U`
  
- **deploying**
  
  deployments will be created from this branch. in order to create a
  deployment, you must allow for a reasonable number of commits to
  accumulate that together make up a *feature*. not every compiling
  credit needs to be packaged and shipped. once you believe the master
  branch has accumulated enough new work, or if the contributors choose
  to repackage, then:
  - create a tag at the current most recent commit/merge in master using
      
    `git tag <name_of_tag>`
    
    the tag you apply must be the tag you intend for the package deployment
    to PyPI. as such, the tag must be [PEP-friendly](https://www.python.org/dev/peps/pep-0425/)
    otherwise deployment will **fail**
  
  - update the package version in `setup.py` with the **same version tag**
    as what you used in the repository
    
  - run `make trigger` to trigger the pipeline on next push (`gitlab-ci`
    is set up to take the hint this way). if you forget to run `make trigger`
    before pushing, the ref will not be deployed.
    deployments must occur on `master`. the pipeline will simply ignore other
    branches.
    
  - commit these changes and push along with tags:
    
    `git push --follow-tags`
    
### dev

- **active development**

  use this branch for active development. if you're developing without `swig`,
  you may want to use the Makefile that is inside the `libcolgraphs` subdirectory
  instead of the Makefile in the root.
  
  once in a while continue to populate `tester.cpp` with tests to make sure your
  code works. please do not merge into `master` without making sure your code works.
  
  
  
- **feature**

  to work on something specific or something new that might break some existing
  methods, please create a new branch so that others can continue to use `dev`
  reliably for their own development. ideally, you would name this new branch by
  an identifying name as to what you're working on. you would never push this
  branch upstream, but only finish working and merge back into dev, and then delete
  the temporary feature/work-in-progress branch.
  
- **pull requests**

  pull requests should be made to `dev`
